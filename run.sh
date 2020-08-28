#!/bin/bash

echo "Compilation bootloader..."
nasm -f bin boot.asm -o boot.bin

echo "Exécution bootloader..."
qemu-system-x86_64 boot.bin
