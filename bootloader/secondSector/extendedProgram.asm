; After the boot sector, the extended program (protected mode, 64 bits...)

jmp enterProtectedMode

%include "time.asm"
%include "GDT.asm"
%include "printString.asm"
%include "memory.asm"

; Protected mode offering 4 GB of RAM, no segmentation, invalid addresses detection
; and task priorities (will be used later by the kernel)
enterProtectedMode:
    call detectMemory
    call enableA20

    ; Disable the system interrupts, we don't need them anymore
    cli

    ; Load GDT
    lgdt [gdt_descriptor]

    ; Clears a bit to indicate protected mode
    mov eax, cr0
    bts eax, 0
    mov cr0, eax

    jmp codeSegment:startProtectedMode

; Legacy stuff to activate the A20 to A32 RAM address lines
; @see http://www.independent-software.com/operating-system-development-enabling-a20-line.html
enableA20:
    ; No idea why
    in al, 0x92
    ; Sets the bit to 1
    or al, 2
    ; No idea why either, but it works
    out 0x92, al
    ret

[bits 32]

%include "CPUID.asm"
%include "paging.asm"

; Flush the CPU pipeline to avoid executing a parallel instruction while migrating to 32 bits
startProtectedMode:
    mov ax, dataSegment
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Moves the stack where there's way more room
    mov ebp, 0x90000
    mov esp, ebp

    call detectCPUID
    call detectLongMode
    call setIdentityPaging
    call editGDT

    jmp codeSegment:start64Bits

[bits 64]
; C function
[extern _start]

%include "IDT.asm"
%include "system.asm"

start64Bits:
    ; VRAM
    mov edi, 0xb8000

    ; 64 bits registry only
    ; 4 spages, bg == 1 == white, fg == f == white
    ; Clear screen
    mov rax, 0x1f201f201f201f20

    ; Lines
    mov ecx, 500

    rep stosq

    call activateSSE

    ; NOTE: Should be overridden after calling _srand, if supported
    mov rcx, 1234567890
    mov [seed], rcx
    call _srand

    ; C function, kernel start
    call _start

    ; End of our kernel execution
    jmp $

; Enables the Streaming SIMD Extensions (SSE)
; Allows operations on floating point like math, comparisons and cast (from double / float or to double / float)
activateSSE:
    ; Set the last bit and unset the penultimate one of cr0
    ; Bit 6 (unsed) : coprocessor emulation
    ; Bit 7 (set) : coprocessor monitoring
    mov rax, cr0
    and ax, 0b11111101
    bts ax, 0
    mov cr0, rax

    ; Set the 2 first bits of cr4
    mov rax, cr4
    or ax, 0b1100000000
    mov cr4, rax

    ret

; To keep a round number of bytes
times 2048-($-$$) db 0
