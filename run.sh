#!/bin/bash

if [ -f ./bootloader.bin ]; then
    mv ./bootloader.bin ./bootloader.bin.bak
fi

if [ -f ./bootloader.bin.part ]; then
    rm ./bootloader.bin.part
fi

if [ -f ./extendedSpace.bin.part ]; then
    rm ./extendedSpace.bin.part
fi

echo "Compilation bootloader..."
nasm bootloader.asm -f bin -o bootloader.bin.part

echo "Compilation secteurs suivants..."
nasm extendedSpace.asm -f bin -o extendedSpace.bin.part

echo "Fusion des fichiers binaires..."
cat bootloader.bin.part extendedSpace.bin.part > bootloader.bin

echo "Exécution bootloader..."
qemu-system-x86_64 -drive format=raw,file=bootloader.bin
