; Some system, low-level stuff
; x64

GLOBAL _exit
; Exit the OS
_exit:
    mov eax, 1
    mov ebx, 0
    int 0x80
    ret


; xorshift64* algorithm
; @ßee https://gist.github.com/anonymous/1ea19a39644f2031fb82#file-t_random-asm
; @see http://vigna.di.unimi.it/ftp/papers/xorshift.pdf

SECTION .bss
    ; 64 bits seed
    seed resq 1

SECTION .text

; Random seed
; () -> void
GLOBAL _srand
_srand:
    ; Request func 1
    mov eax, 1
    ; Request subfunc 0
    mov ecx, 0

    cpuid
    ; Test if srand supported
    test ecx, 1 << 30

    jz noRdrand

    mov ecx, 100 ; Number of tries
    retry:
        rdrand eax
        jc .done ; Carry flag set when success
        loop retry
    .fail:
        ; No available random number
    .done:
    mov [seed], eax
    jmp exitSrand

    noRdrand:
    call _randint

    exitSrand:
    ret

GLOBAL _getSeed
_getSeed:
    mov eax, [seed]
    ret

; Random seed
; (u64 newSeed:esi) -> void
GLOBAL _srands
_srands:
    mov [seed], esi
    ret

; () -> u64:rcx
; Pseudo randomized qwad word
GLOBAL _randint
_randint:
    mov rcx, [seed]
    mov rdx, rcx
    shr rdx, 12
    xor rcx, rdx
    mov rdx, rcx
    shl rdx, 25
    xor rcx, rdx
    mov rdx, rcx
    shr rdx, 27
    xor rcx, rdx
    mov rax, 2685821657736338717
    mul rcx
    mov [seed], rcx
    ret
