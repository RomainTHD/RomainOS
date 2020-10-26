GLOBAL _memoryRegionCount
_memoryRegionCount:
    db 0

detectMemory:
    ; Set ES et DI à la destination d'où stocker la table
    mov ax, 0
    mov es, ax
    mov di, 0x5000 ; Destination au pif
    mov edx, 0x534d4150 ; "SMAP" en ASCII
    xor ebx, ebx ; Set à 0, on aurait aussi pu faire "mov ebx, 0" mais c'est pas drôle ahah

    ; Loop, on va parcourir le listing de la table et sauvegarder la RAM via le BIOS
    .loopMemory:
        ; Pour setup l'interruption
        mov eax, 0xe820

        ; Taille de 8 memory listing, pour le BIOS, ça marche c'est magique
        mov ecx, 24

        ; Sauvegarde le memory listing dans notre table
        int 0x15

        ; Fin ou non du listing
        cmp ebx, 0
        je .finishedLoopMemory

        ; Incrémente le destination index
        add di, 24

        ; Nouveau listing
        inc byte [_memoryRegionCount]

        jmp .loopMemory

    .finishedLoopMemory:
    ret

