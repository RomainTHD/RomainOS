MAKEFLAGS += --silent

GCC_PATH = "$$HOME"/opt/cross/bin/x86_64-elf-g++
LINKER_PATH = "$$HOME"/opt/cross/bin/x86_64-elf-ld

all: compileAsm compileCPP link merge calcNbSeg run

compileAsm:
	echo "Compilation bootloader..."
	cd ./src/bootSector && \
	nasm ./bootloader.asm -f bin -o ../../bin/part/bootloader.bin -w+orphan-labels

	echo "Compilation secteurs suivants..."
	cd ./src/secondSector && \
	nasm ./extendedProgram.asm -f elf64 -i ../bootSector/ -o ../../bin/part/extendedProgram.o -w+orphan-labels  && \
	nasm ./binaries.asm -f elf64 -o ../../bin/part/binaries.o -w+orphan-labels

compileCPP:
	echo "Compilation C/C++..."

	cd ./src && \
	$(GCC_PATH) -Ttext 0x8000 \
				-ffreestanding \
				-lstdc++ \
				-mno-red-zone \
				-m64 \
				-Wall \
				-Wextra \
				-pedantic \
				-Wno-write-strings \
				-std=c++1z \
				-I . \
				-c kernel.cpp \
				-o ../bin/part/kernel.o \

link:
	echo "Linker..."
	cd ./bin/part && \
	$(LINKER_PATH) -T "../../linker.ld"

merge:
	echo "Fusion des fichiers binaires..."
	cat ./bin/part/bootloader.bin ./bin/part/kernel.bin > ./bin/OS/RomainOS.bin

calcNbSeg:
	echo "; Fichier généré automatiquement." > src/bootSector/diskReadSegments.asm
	echo "; La valeur est calculée selon l'espace occupé par le fichier binaire final." >> src/bootSector/diskReadSegments.asm
	nbSeg=$$(($$(wc -c < ./bin/OS/RomainOS.bin)/512)) && \
	echo "Nombre de segments nécessaires: $$nbSeg" && \
	echo "mov al," $$nbSeg >> src/bootSector/diskReadSegments.asm

run:
	echo "Exécution bootloader..."
	qemu-system-x86_64 \
				-m 16 \
				-drive format=raw,file=./bin/OS/RomainOS.bin \
				--no-reboot

iso:
	dd bs=512 count=2880 if=/dev/zero of=./bin/part/disk.img
	dd if=./bin/OS/RomainOS.bin of=./bin/part/disk.img conv=notrunc
	rm -r ./bin/part/cd_content
	mkdir ./bin/part/cd_content
	cp ./bin/part/disk.img ./bin/part/cd_content
	cd ./bin/part && \
	mkisofs -o ../OS/RomainOS.iso -V RomainOS -b disk.img cd_content
