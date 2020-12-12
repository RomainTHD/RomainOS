MAKEFLAGS += --silent

.PHONY: all
all: clean build

.PHONY: build
build: build-efi

.PHONY: build-efi
build-efi:
	gcc -Wall -Wextra -pedantic -m64 -mabi=ms -ffreestanding -mno-red-zone -std=c++1z -save-temps=obj -Wno-write-strings -I ./libc/include -c ./efi/efi_main.cpp -o ./obj/efi/efi_main.o
	cd ./obj/efi && \
	gcc -Wall -Wextra -pedantic -m64 -mabi=ms -nostdlib -shared -Wl,-dll -Wl,--subsystem,10 -e efiMain -o ../../bin/BOOTX64.EFI ./efi_main.o

# -Wall                 Toutes les erreurs
# -Wextra               Extra erreurs
# -pedantic             Erreurs en plus
# -m64                  Génère du code pour 64 bits
# -mabi=ms              Sélectionne l'ABI utilisée (déjà expliqué dans RomainOS BIOS donc flemme)
# -ffreestanding        La lib standard n'existe pas, et main n'est pas le point d'entrée
# -mno-red-zone         Désactive la red-zone, 128 bytes sous le stack utilisés librement par gcc
# -std=c++1z            C++ 17
# -save-temps=obj       Exporte les .cpp en assembleur dans le même dossier que les .o
# -Wno-write-strings    Disable les warnings pour l'utilisation de char* au lieu de std::string (std::string n'existe pas)

# -nostdlib             Pas de lib standarde
# -shared
# -Wl,-dll              Windows stuff
# -Wl,--subsystem,10    Windows stuff encore
# -e efiMain            Point d'entrée

.PHONY: clean
clean:
	rmdir /s /q obj
	mkdir obj
	mkdir obj\efi
