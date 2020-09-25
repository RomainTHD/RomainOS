; Affiche une chaine de caractères terminée par '\0'
printStringBIOS:
    push ax
    push bx

    ; BIOS set en mode TTY
    mov ah, 0x0e

    .loopPrintString:

    ; Comparaison de bx et de \0
    cmp [bx], byte 0

    ; Check le flag d'égalité, si == alors jmp exitPrintString
    je .exitPrintString
        ; Registre d'écriture
        mov al, [bx]
        ; Interruption BIOS pour écrire le contenu de al
        int 0x10
        ; Incrémente bx pour passer au caractère suivant
        inc bx
        jmp .loopPrintString
    .exitPrintString:

    pop ax
    pop bx
    ret
