#!/bin/bash

if [ -f ./bootloader.bin ]; then
    mv ./bootloader.bin ./bootloader.bin.bak
fi

echo "Compilation bootloader..."
nasm bootloader.asm -f bin -o bootloader.bin.part

echo "Compilation secteurs suivants..."
nasm nextSectors.asm -f bin -o nextSectors.bin.part

echo "Fusion des fichiers binaires..."
cat bootloader.bin.part nextSectors.bin.part > bootloader.bin

echo "Exécution bootloader..."
qemu-system-x86_64 -drive format=raw,file=bootloader.bin
