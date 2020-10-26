GLOBAL _exit
; Quitte l'OS
_exit:
    mov eax, 1
    mov ebx, 0
    int 0x80
    ret


; Algorithme xorshift64*
; Cf. https://gist.github.com/anonymous/1ea19a39644f2031fb82#file-t_random-asm
; Cf. http://vigna.di.unimi.it/ftp/papers/xorshift.pdf

SECTION .bss
    ; Seed 64 bits
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
    ; Test si présence rdrand
    test ecx, 1 << 30

    jz noRdrand

    mov ecx, 100 ; Nb essais
    retry:
        rdrand eax
        jc .done ; Carry flag set quand succès
        loop retry
    .fail:
        ; Pas de nb random available
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
