GLOBAL _exit
; Quitte l'OS
_exit:
    mov eax, 1
    mov ebx, 0
    int 0x80
    ret
