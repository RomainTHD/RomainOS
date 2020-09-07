#!/bin/bash

if [ -f ./bin/bootloader.bin ]; then
    mv ./bin/bootloader.bin ./bin/bootloader.bin.bak
fi

if [ -f ./bin/bootloader.bin.part ]; then
    rm ./bin/bootloader.bin.part
fi

if [ -f ./bin/extendedSpace.bin.part ]; then
    rm ./bin/extendedSpace.bin.part
fi

cd ./src || exit

echo "Compilation bootloader..."
nasm ./bootloader.asm -f bin -o ../bin/bootloader.bin.part || exit

echo "Compilation secteurs suivants..."
nasm ./extendedSpace.asm -f bin -o ../bin/extendedSpace.bin.part || exit

cd ..

echo "Fusion des fichiers binaires..."
cat ./bin/bootloader.bin.part ./bin/extendedSpace.bin.part > ./bin/bootloader.bin || exit

echo "Exécution bootloader..."
qemu-system-x86_64 -drive format=raw,file=./bin/bootloader.bin
