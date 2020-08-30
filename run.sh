#!/bin/bash

if [ -f ./boot.bin ]; then
    mv ./boot.bin ./boot.bin.bak
fi

echo "Compilation bootloader..."
nasm -f bin boot.asm -o boot.bin

echo "Exécution bootloader..."
qemu-system-x86_64 boot.bin
