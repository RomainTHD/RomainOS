; Interrupt Descriptor Table, x64 only

[extern _idt]
IDTDescriptor:
    ; 256 entries * 16 bytes
    dw 4095

    ; IDT used by the linker
    dq _idt

; Backup the registry state
%macro PUSHALL 0
    push rax
    push rcx
    push rdx
    push r8
    push r9
    push r10
    push r11
%endmacro

; Load the regirstry state
%macro POPALL 0
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdx
    pop rcx
    pop rax
%endmacro

; Will be defined in the kernel
[extern isr1Handler]

; isr1 is usable by the C++ kernel
GLOBAL _isr1
; Interrupt service routine 1, == keyboard
_isr1:
    ; So we can keep the registry state
    PUSHALL
    call isr1Handler
    POPALL
    ; 64 bits so quad
    iretq

GLOBAL _loadIDT
; Loads the IDT interrupts
_loadIDT:
    lidt [IDTDescriptor]
    ; Enable the IDT interrupts
    sti
    ret
