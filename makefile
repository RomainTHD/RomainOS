MAKEFLAGS += --silent

GCC_PATH = "$$HOME"/opt/cross/bin/x86_64-elf-g++
LINKER_PATH = "$$HOME"/opt/cross/bin/x86_64-elf-ld

SRCDIR := .
OBJDIR := ./obj
DEPDIR := dep
SRCS   := $(shell find $(SRCDIR) -name "*.cpp")
OBJS   := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS   := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)
TREE   := $(patsubst %/,%,$(dir $(OBJS)))

CPPFLAGS = -Ttext 0x8000 -ffreestanding -mno-red-zone -fno-exceptions -m64 -save-temps=obj -Wall -Wextra -pedantic -Wno-write-strings -std=c++1z -I ./libc/include
# -Ttext 0x8000             Sets the .text section to 0x8000 to locate the main
# -ffreestanding            There's no standard library and main isn't the entry point
# -mno-red-zone             Disable the red-zone, 128 bytes under the stack freely used by gcc
# -fno-exceptions           Disable the code generation for C++ exceptions (because they don't exist, duh)
# -m64                      Generate 64 bits code
# -save-temps=obj           Exports the .cpp to assembly in the same directory as the .o
# -Wall                     All warnings
# -Wextra                   Extra warnings
# -pedantic                 Even more warnings
# -Wno-write-strings        Disable the warnings due to the use of `char*` instead of `std::string` (because it doesn't exist)
# -std=c++1z                C++17
# -I ./libc/include         Include directory for C/C++ libraries

all: clean build run

build: compileAsm compileCPP link merge calcNbSeg

clean:
	rm -r ./obj
	mkdir ./obj
	rm -r ./bin/part
	mkdir ./bin/part

compileAsm:
	echo "Bootloader compilation..."
	cd ./bootloader/bootSector && \
	nasm ./bootloader.asm -f bin -o ../../bin/part/bootloader.bin -w+orphan-labels

	echo "Next sectors compilation..."
	cd ./bootloader/secondSector && \
	nasm ./extendedProgram.asm -f elf64 -i ../bootSector/ -o ../../obj/extendedProgram.o -w+orphan-labels  && \
	nasm ./binaries.asm -f elf64 -o ../../obj/binaries.o -w+orphan-labels

compileCPP: _beforeCompilationCPP $(OBJS) _afterCompilationCPP

_beforeCompilationCPP:
	echo "C/C++ compilation..."

.SECONDEXPANSION:
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)
	$(GCC_PATH) $(CPPFLAGS) -o $@ -c $<

$(TREE): %:
	mkdir -p $@
	mkdir -p $(@:$(OBJDIR)%=$(DEPDIR)%)

_afterCompilationCPP:
	python3 ./scripts/editLinker.py

link:
	echo "Linker..."
	$(LINKER_PATH) -T "./scripts/linker.ld"

merge:
	echo "Binary files merge..."
	cat ./bin/part/bootloader.bin ./bin/part/kernel.bin > ./bin/OS/RomainOS.bin

calcNbSeg:
	echo "; AUTO-GENERATED FILE" > ./bootloader/bootSector/diskReadSegments.asm
	echo "; This value is calculated using the final binary file size." >> ./bootloader/bootSector/diskReadSegments.asm
	nbSeg=$$(($$(wc -c < ./bin/OS/RomainOS.bin)/512)) && \
	echo "Number of necessary segments : $$nbSeg" && \
	echo "mov al," $$nbSeg >> ./bootloader/bootSector/diskReadSegments.asm

run:
	echo "Bootloader execution..."
	qemu-system-x86_64 -drive format=raw,file=./bin/OS/RomainOS.bin --no-reboot

iso: build
	dd bs=512 count=2880 if=/dev/zero of=./bin/part/disk.img
	dd if=./bin/OS/RomainOS.bin of=./bin/part/disk.img conv=notrunc
	rm -rf ./bin/part/cd_content
	mkdir ./bin/part/cd_content
	cp ./bin/part/disk.img ./bin/part/cd_content
	cd ./bin/part && \
	mkisofs -o ../OS/RomainOS.iso -V RomainOS -b disk.img cd_content
