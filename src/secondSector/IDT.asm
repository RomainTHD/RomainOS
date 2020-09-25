[extern _idt]
IDTDescriptor:
    ; 256 entries * 16 bytes
    dw 4095

    ; IDT utilisé par le linker
    dq _idt

; Garde l'état des registres
%macro PUSHALL 0
    push rax
    push rcx
    push rdx
    push r8
    push r9
    push r10
    push r11
%endmacro

; Récupère l'état des registres
%macro POPALL 0
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdx
    pop rcx
    pop rax
%endmacro

[extern isr1Handler]

; Rend isr1 global et donc utilisable par le kernel C++
GLOBAL _isr1
; Interrupt service routine 1, = keyboard
_isr1:
    ; Pour maintenir l'état des registres
    PUSHALL
    call isr1Handler
    POPALL
    ; Interrupt return quad (car 64 bits)
    iretq

GLOBAL _loadIDT
; Charge les interruptions IDT
_loadIDT:
    lidt [IDTDescriptor]
    ; Active les interruptions IDT
    sti
    ret
