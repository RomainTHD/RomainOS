; GDT: structure defining the RAM (access, size, system privileges...)
; x86

; GDT Null Descriptor
gdt_nullDesc:
    dd 0
    dd 0

; Code segment descriptor, executable
; Structure:
; [ 0, 15]: Limit 0:15
; [16, 31]: Base 0:15
; [32, 39]: Base 16:23
; [40, 47]: Access byte
; [48, 51]: Limit 16:19
; [52, 55]: Flags
; [56, 63]: Base 24:31
gdt_codeSegmentDesc:
    ; Limit, entierly covers the RAM
    dw 0xffff
    ; Base (low)
    dw 0x0000
    ; Base (med)
    db 0x00

    ; Access byte (flags)
    ; 1, Pr         : Valid sectors, "present" or "not present" => marked as ignored
    ; 00, Privil    : Privilege, 0 to 3, kernel level here so 0
    ; 1, S          : Descriptor top, 1 for code and data segments, 0 for system segment
    ; 1, Ex         : Executable or not
    ; 0, DC         : Direction, if it can be executed with less privileges or if it requires Pr
    ; 1, RW         : Readable or not
    ; 0, Ac         : Sets by the CPU when the segmen is accessed
    db 10011010b

    ; Flags + upper limit
    ; 1, Gr         : Granularity, limit in 4 kB blocs or in bytes
    ; 1, Sz         : Size, 32-bits protected or 16-bits protected
    ; 00            : Not used here
    ; 1111          : Limit
    db 11001111b

    ; Base (high)
    db 0x00

; Data segment descriptor, not executable
; Almost identical to codeSegmentDesc
gdt_dataSegmentDesc:
    dw 0xffff
    dw 0x0000
    db 0x00
    ; Not executable
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    gdt_size:
        dw gdt_end - gdt_nullDesc - 1
        dq gdt_nullDesc

codeSegment equ gdt_codeSegmentDesc - gdt_nullDesc
dataSegment equ gdt_dataSegmentDesc - gdt_nullDesc

[bits 32]
; GDT goes to x64
editGDT:
    mov [gdt_codeSegmentDesc + 6], byte 10101111b
    mov [gdt_dataSegmentDesc + 6], byte 10101111b
    ret

[bits 16]
; FIXME: Shouldn't it be in extendedProgram ?
