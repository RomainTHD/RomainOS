; Bootloader, first bytecode loaded, 16 bits only

; Load all the program to the offset 0x7c00
[org 0x7c00]

; Disk number
mov [BOOT_DISK], dl

; Stack creation at 0x7c00
mov bp, 0x7c00
; Stack pointer == current memory address
mov sp, bp

call readDisk

; Jump to next sectors
jmp PROGRAM_SPACE

%include "printString.asm"
%include "diskRead.asm"

; Write the end of the boot sector (first 512 bytes of the disk, ended by 0x55 0xaa) to boot the OS
; Writes 0 until 2 bytes before the end of the boot sector
; $$ : current section section, 1st line address
; Thus ($ - $$) == precedent code size
times 510-($-$$) db 0

; 2 last boot sector bytes
db 0x55, 0xaa
