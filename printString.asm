printString:
    ; BIOS set en mode TTY
    mov ah, 0x0e

    .loopPrintString:

    ; Comparaison de bx et de \0
    cmp [bx], byte 0

    ; Check le flag d'égalité, si == alors jmp exitPrintString
    je .exitPrintString
        ; Registre d'écriture
        mov al,[bx]
        ; Interruption BIOS pour écrire le contenu de al
        int 0x10
        ; Incrémente bx pour passer au caractère suivant
        inc bx
        jmp .loopPrintString

    .exitPrintString:
    ; Return
    ret

testString:
    ; String terminée par '\0'
    db "Test OK", 0
