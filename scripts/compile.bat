cd ..

gcc -Wall -Wextra -pedantic -m64 -mabi=ms -ffreestanding -mno-red-zone  -std=c++1z -save-temps=obj -Wno-write-strings -c ./efi/efi_main.cpp -o ./obj/efi/efi_main.o

cd ./obj/efi

gcc -Wall -Wextra -pedantic -m64 -mabi=ms -nostdlib -shared -Wl,-dll -Wl,--subsystem,10 -e efiMain -o ../../bin/BOOTX64.EFI ./efi_main.o

pause
