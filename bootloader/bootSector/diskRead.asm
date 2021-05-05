; Disk utilities and stuff
; 16 bits only

; 512 bytes after 0x7c00
PROGRAM_SPACE equ 0x8000

; Reads the disk
readDisk:
    ; Configure BIOS to read the disk
    mov ah, 0x02

    ; So the BIOS know where to load data in mémoire
    mov bx, PROGRAM_SPACE

    ; Number of 512 bytes sectors on the disk
    ; TODO: %include "diskReadSegments.asm"
    mov al, 127

    ; Which disk to choose
    mov dl, [BOOT_DISK]

    ; Cylinder number 0 (hard drive)
    mov ch, 0x00

    ; Head number 0 (hard drive)
    mov dh, 0x00

    ; Starts reading at the 2nd secteur (the 1st one being the boot sector)
    mov cl, 0x02

    ; Main reading loop
    diskReadLoop:
        ; FIXME: Shouldn't we push and pop ?
        ; push ax
        ; push bx
        ; push cx
        ; push dx

        ; BIOS interrupt to read
        int 0x13

        ; pop dx
        ; pop cx
        ; pop bx
        ; pop ax

        ; Jump if carry set, if there's an error on the disk
        jc diskReadExit
        ; FIXME: why not `jc diskReadError` ?

        ; Writes the next 512 bytes
        add bx, 512
        ; Reads the next sector
        inc cx

        ; Hard limit of 255 sectors
        cmp cl, 255
        je diskReadExit

        jmp diskReadLoop

    ; Exit loop
    diskReadExit:
        ; pop dx
        ; pop cx
        ; pop bx
        ; pop ax

    ret

diskReadErrorString:
    db "Disk read failed", 0

diskReadError:
    mov bx, diskReadErrorString
    call printStringBIOS
    ; Infinite loop but we don't really care here, the failure is unrecoverable
    jmp $

BOOT_DISK:
    db 0
