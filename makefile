MAKEFLAGS += --silent

GCC_PATH = "$$HOME"/opt/cross/bin/x86_64-elf-g++
LINKER_PATH = "$$HOME"/opt/cross/bin/x86_64-elf-ld

all: clean build run

build: compileAsm compileCPP link merge calcNbSeg

clean:
	rm -r bin/part
	mkdir bin/part

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
				-mno-red-zone \
				-m64 \
				-save-temps=obj \
				-Wall \
				-Wextra \
				-pedantic \
				-Wno-write-strings \
				-std=c++1z \
				-I . \
				-c kernel.cpp \
				-o ../bin/part/kernel.o

	# -Ttext 0x8000				Set la section .text à 0x8000, pour situer le main
	# -ffreestanding			La lib standard n'existe pas, et main n'est pas le point d'entrée
	# -mno-red-zone				Désactive la red-zone, 128 bytes sous le stack utilisés librement par gcc
	# -m64						Génère du code pour 64 bits
	# -save-temps=obj			Exporte les .cpp en assembleur dans le même dossier que les .o
	# -Wall						Toutes les erreurs
	# -Wextra					Extra erreurs
	# -pedantic					Erreurs en plus
	# -Wno-write-strings		Disable le warning pour l'utilisation de char* au lieu de std::string (std::string n'existe pas...)
	# -std=c++1z				C++ 17
	# -I .						Dossier d'includes pour les .hpp
	# -c kernel.cpp				Source
	# -o ../bin/part/kernel.o	Output

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
				-m 64 \
				-drive format=raw,file=./bin/OS/RomainOS.bin \
				--no-reboot

iso: build
	dd bs=512 count=2880 if=/dev/zero of=./bin/part/disk.img
	dd if=./bin/OS/RomainOS.bin of=./bin/part/disk.img conv=notrunc
	rm -rf ./bin/part/cd_content
	mkdir ./bin/part/cd_content
	cp ./bin/part/disk.img ./bin/part/cd_content
	cd ./bin/part && \
	mkisofs -o ../OS/RomainOS.iso -V RomainOS -b disk.img cd_content
