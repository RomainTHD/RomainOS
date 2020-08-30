; BIOS set en mode TTY
mov ah, 0x0e

; Registre d'écriture set à 'A'
mov al, 'A'

loop:
    ; Interruption BIOS pour écrire le contenu de al
    int 0x10

    ; Changement vers minuscule
    add al, ('a' - 'A')
    int 0x10

    ; Compare al et 'z'
    cmp al, 'z'

    ; Check le flag d'égalité, si == alors jmp exit
    je exit

    ; Incrémente al et le passe en majuscule
    sub al, ('a' - 'A' - 1)

    jmp loop

exit:
    ; Jump à l'adresse de la ligne courante pour écraser le reste du disque avec des 0
    jmp $

    ; Écriture du boot sector (512 premiers bytes du disque terminés par 0x55 0xaa) pour booter l'OS
    ; Répète "db 0" (écrit 0) jusqu'à 2 bytes avant la fin du boot sector
    ; $$ : début de la section courante, adresse de la 1ère ligne
    ; Par déduction, ($ - $$) = taille du code précédent
    times 510-($-$$) db 0

    ; Écriture des 2 derniers bytes du boot sector
    db 0x55, 0xaa
