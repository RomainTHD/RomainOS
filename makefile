MAKEFLAGS += --silent

GCC_PATH = "$$HOME"/opt/cross/bin/x86_64-elf-g++
LINKER_PATH = "$$HOME"/opt/cross/bin/x86_64-elf-ld

all: compileAsm compileCPP link merge calcNbSeg run

compileAsm:
	echo "Compilation bootloader..."
	cd ./src/bootSector && \
	nasm ./bootloader.asm -f bin -o ../../bin/bootloader.bin -w+orphan-labels

	echo "Compilation secteurs suivants..."
	cd ./src/secondSector && \
	nasm ./extendedProgram.asm -f elf64 -o ../../bin/extendedProgram.o -w+orphan-labels  && \
	nasm ./binaries.asm -f elf64 -o ../../bin/binaries.o -w+orphan-labels

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
				-I . \
				-c kernel.cpp \
				-o ../bin/kernel.o \

link:
	echo "Linker..."
	cd ./bin && \
	$(LINKER_PATH) -T "../linker.ld"

merge:
	echo "Fusion des fichiers binaires..."
	cat ./bin/bootloader.bin ./bin/kernel.bin > ./bin/RomainOS.bin

calcNbSeg:
	nbSeg=$(expr "$(wc -c < ./bin/RomainOS.bin)" / 512)
	echo "Nombre de segments nécessaires:" $nbSeg
	echo "; Fichier généré automatiquement par le script 'run.sh' selon l'espace occupé par le fichier binaire final" > src/bootSector/diskReadSegments.asm
	# echo "mov al," $nbSeg >> src/bootSector/diskReadSegments.asm
	echo "mov al, 26" >> src/bootSector/diskReadSegments.asm

run:
	echo "Exécution bootloader..."
	qemu-system-x86_64 -m 16 -drive format=raw,file=./bin/RomainOS.bin || exit
