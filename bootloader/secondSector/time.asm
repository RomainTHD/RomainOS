; Time related functions
; x86

; Time structure
timeval:
    tv_sec  dw 0
    tv_nsec dw 0

GLOBAL _sleep
_sleep:
    ; Syscall
    mov eax, 162
    ; Time
    mov ebx, timeval
    mov ecx, 0
    ; Interrup
    int 0x80
    ret
