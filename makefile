MAKEFLAGS += --silent

GCC_PATH = "$$HOME"/opt/cross/bin/x86_64-elf-g++
LINKER_PATH = "$$HOME"/opt/cross/bin/x86_64-elf-ld

SRCDIR := ./src
OBJDIR := ./obj
DEPDIR := dep
SRCS   := $(shell find $(SRCDIR) -name "*.cpp")
OBJS   := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS   := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)
TREE   := $(patsubst %/,%,$(dir $(OBJS)))

CPPFLAGS = -Ttext 0x8000 -ffreestanding -mno-red-zone -fno-exceptions -m64 -save-temps=obj -Wall -Wextra -pedantic -Wno-write-strings -std=c++1z -I ./include -I ./include/std
# -Ttext 0x8000             Set la section .text à 0x8000, pour situer le main
# -ffreestanding            La lib standard n'existe pas, et main n'est pas le point d'entrée
# -mno-red-zone             Désactive la red-zone, 128 bytes sous le stack utilisés librement par gcc
# -fno-exceptions           Désactive la génération de code pour les exceptions (vu qu'elles n'existent pas)
# -m64                      Génère du code pour 64 bits
# -save-temps=obj           Exporte les .cpp en assembleur dans le même dossier que les .o
# -Wall                     Toutes les erreurs
# -Wextra                   Extra erreurs
# -pedantic                 Erreurs en plus
# -Wno-write-strings        Disable les warnings pour l'utilisation de char* au lieu de std::string (std::string n'existe pas...)
# -std=c++1z                C++ 17
# -I ./src                  Dossier d'include pour les .hpp
# -I ./src/std              Dossier d'include pour les .hpp : std

all: clean build run

build: compileAsm compileCPP link merge calcNbSeg

clean:
	rm -r ./obj
	mkdir ./obj
	rm -r ./bin/part
	mkdir ./bin/part

compileAsm:
	echo "Compilation bootloader..."
	cd ./src/kernel/bootSector && \
	nasm ./bootloader.asm -f bin -o ../../../bin/part/bootloader.bin -w+orphan-labels

	echo "Compilation secteurs suivants..."
	cd ./src/kernel/secondSector && \
	nasm ./extendedProgram.asm -f elf64 -i ../bootSector/ -o ../../../obj/extendedProgram.o -w+orphan-labels  && \
	nasm ./binaries.asm -f elf64 -o ../../../obj/binaries.o -w+orphan-labels

compileCPP: _beforeCompilationCPP $(OBJS) _afterCompilationCPP

_beforeCompilationCPP:
	echo "Compilation C/C++..."

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
	echo "Fusion des fichiers binaires..."
	cat ./bin/part/bootloader.bin ./bin/part/kernel.bin > ./bin/OS/RomainOS.bin

calcNbSeg:
	echo "; Fichier généré automatiquement." > src/kernel/bootSector/diskReadSegments.asm
	echo "; La valeur est calculée selon l'espace occupé par le fichier binaire final." >> src/kernel/bootSector/diskReadSegments.asm
	nbSeg=$$(($$(wc -c < ./bin/OS/RomainOS.bin)/512)) && \
	echo "Nombre de segments nécessaires: $$nbSeg" && \
	echo "mov al," $$nbSeg >> src/kernel/bootSector/diskReadSegments.asm

run:
	echo "Exécution bootloader..."
	qemu-system-x86_64 -drive format=raw,file=./bin/OS/RomainOS.bin --no-reboot

iso: build
	dd bs=512 count=2880 if=/dev/zero of=./bin/part/disk.img
	dd if=./bin/OS/RomainOS.bin of=./bin/part/disk.img conv=notrunc
	rm -rf ./bin/part/cd_content
	mkdir ./bin/part/cd_content
	cp ./bin/part/disk.img ./bin/part/cd_content
	cd ./bin/part && \
	mkisofs -o ../OS/RomainOS.iso -V RomainOS -b disk.img cd_content
