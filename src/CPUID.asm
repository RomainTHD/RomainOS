; Flip un bit, s'il reste identique alors CPUID est supporté
detectCPUID:
    ; Push flags dans le stack
    pushfd
    pop eax

    ; Backup eax
    mov ecx, eax

    ; Flip un bit
    xor eax, 1 << 21

    ; Pop eax dans flags
    push eax
    popfd

    ; Restore flags à ancienne version
    push ecx
    popfd

    ; Check différence
    xor eax, ecx

    ; jmp if zero
    jz noCPUID

    ret

; No CPUID support
noCPUID:
    hlt

; Détection du long-mode pour 64-bits mode
detectLongMode:
    ; Gros nombre
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz noLongMode
    ret

; No long-mode support
noLongMode:
    hlt
