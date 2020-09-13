#!/bin/bash

if [ -f ./bin/RomainOS.bin ]; then
    mv ./bin/RomainOS.bin ./bin/RomainOS.bin.bak
fi

echo "Compilation bootloader..."
cd ./src/bootSector || exit
nasm ./bootloader.asm -f bin -o ../../bin/bootloader.bin || exit

echo "Compilation secteurs suivants..."
cd ../secondSector || exit
nasm ./extendedProgram.asm -f elf64 -o ../../bin/extendedProgram.o || exit

echo "Compilation C/C++..."
cd .. || exit
"$HOME"/opt/cross/bin/x86_64-elf-g++ -Ttext 0x8000 -ffreestanding -lstdc++ -mno-red-zone -m64 -c kernel.cpp -Wall -Wextra -pedantic -o ../bin/kernel.o || exit

echo "Linker..."
cd ../bin || exit
"$HOME"/opt/cross/bin/x86_64-elf-ld -T "../linker.ld" || exit

echo "Fusion des fichiers binaires..."
cd ..
cat ./bin/bootloader.bin ./bin/kernel.bin > ./bin/RomainOS.bin || exit

echo "Exécution bootloader..."
qemu-system-x86_64 -drive format=raw,file=./bin/RomainOS.bin || exit

echo "Fin normale du programme"
