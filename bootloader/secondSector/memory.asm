; RAM
; 16 bits if I remember well

GLOBAL _memoryRegionCount
_memoryRegionCount:
    db 0

detectMemory:
    ; Set ES and DI to the destination where we want to store the table
    mov ax, 0
    mov es, ax
    mov di, 0x5000 ; Whatever destination you want
    mov edx, 0x534d4150 ; "SMAP" in ASCII
    xor ebx, ebx ; Sets to 0, yea we could use "mov ebx, 0" but it's less fun

    ; We're going to save the RAM using the BIOS looping through the table listing
    .loopMemory:
        ; Interruption setup
        mov eax, 0xe820

        ; 8 memory listing, for the BIOS, idk why it works but trials and errors
        mov ecx, 24

        ; Save the memory listing in our table
        int 0x15

        ; End of the listing or not
        cmp ebx, 0
        je .finishedLoopMemory

        ; Increments the destination index
        add di, 24

        ; New listing
        inc byte [_memoryRegionCount]

        jmp .loopMemory

    .finishedLoopMemory:
    ret

