; CPUID detection

; Flips a bit, if the bit isn't changed then CPUID is supported
detectCPUID:
    ; Push flags to stack as a backup
    pushfd
    pop eax

    ; Backup eax
    mov ecx, eax

    ; Flip the bit
    xor eax, 1 << 21

    ; Pop eax to the flags
    push eax
    popfd

    pushfd
    pop eax

    ; Restore the flags to the old version
    push ecx
    popfd

    ; Check the difference
    xor eax, ecx

    ; Jump if zero
    jz noCPUID

    ret

; No CPUID support, can't continue
noCPUID:
    hlt

; Long-mode for 64-bits detection
detectLongMode:
    ; Big number just to check
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz noLongMode
    ret

; No long-mode support
noLongMode:
    hlt
