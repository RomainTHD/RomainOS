#!/bin/bash

export PATH="$HOME/opt/cross/bin:$PATH"

if [ -f ./bin/RomainOS.bin ]; then
    mv ./bin/RomainOS.bin ./bin/RomainOS.bin.bak
fi

cd ./src || exit

echo "Compilation bootloader..."
nasm ./bootloader.asm -f bin -o ../bin/bootloader.bin || exit

echo "Compilation secteurs suivants..."
nasm ./extendedSpace.asm -f elf64 -o ../bin/extendedSpace.o || exit

x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c "kernel.cpp" -o "../bin/kernel.o" || exit

cd ../bin || exit

x86_64-elf-ld -o ./kernel.tmp -Ttext 0x7e00 ./extendedSpace.o ./kernel.o || exit

objcopy -O binary ./kernel.tmp ./kernel.bin

cd ..

echo "Fusion des fichiers binaires..."
cat ./bin/bootloader.bin ./bin/kernel.bin > ./bin/RomainOS.bin || exit

echo "Exécution bootloader..."
qemu-system-x86_64 -drive format=raw,file=./bin/RomainOS.bin
