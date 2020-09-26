; Structure de temps
timeval:
    tv_sec  dw 0
    tv_nsec dw 0

GLOBAL _sleep
_sleep:
    ; Syscall
    mov eax, 162
    ; Temps
    mov ebx, timeval
    mov ecx, 0
    ; Interruption
    int 0x80
    ret
