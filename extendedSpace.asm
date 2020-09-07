[org 0x7e00]

mov bx, extendedSpaceSuccessString
call printString

; Boucle infinie, fin
jmp $

%include "printString.asm"

extendedSpaceSuccessString:
    db "Secteurs suivants bien charges", 0

times 2048-($-$$) db 0
