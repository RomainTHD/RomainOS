; 512 bytes apres 0x7c00
PROGRAM_SPACE equ 0x8000

readDisk:
    ; Configure le BIOS pour lire le disque
    mov ah, 0x02

    ; Pour que le BIOS sache où mettre la data en mémoire
    mov bx, PROGRAM_SPACE

    ; Nombre de secteurs de 512 bytes du disque
    ; %include "diskReadSegments.asm"
    mov al, 127

    ; Quel disque choisir
    mov dl, [BOOT_DISK]

    ; Cylindre num 0 (hard drive)
    mov ch, 0x00

    ; Head num 0 (hard drive)
    mov dh, 0x00

    ; Lecture à partir du 2e secteur, le 1er étant le boot sector
    mov cl, 0x02

    diskReadLoop:
        ; push ax
        ; push bx
        ; push cx
        ; push dx

        ; Interruption BIOS pour lire
        int 0x13

        ; pop dx
        ; pop cx
        ; pop bx
        ; pop ax

        ; Bon, l'avenir nous dira si ce code était une erreur ou non...
        ; Jmp if carry set (= erreur disque)
        jc diskReadExit
        ; Autre possibilité:
        ; jc diskReadError

        ; Écriture des 512 bytes suivants
        add bx, 512
        ; Lecture secteur suivant
        inc cx

         ; limite de 255 secteurs
        cmp cl, 255
        je diskReadExit

        jmp diskReadLoop

    diskReadExit:
        ; pop dx
        ; pop cx
        ; pop bx
        ; pop ax

    ret

diskReadErrorString:
    db "Disk read failed", 0

diskReadError:
    mov bx, diskReadErrorString
    call printStringBIOS
    ; Boucle infinie parce que erreur de toute façon
    jmp $

BOOT_DISK:
    db 0
