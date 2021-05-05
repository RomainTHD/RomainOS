; Prints the string
; 16 bits-only I think ? Because BIOS only

; Outputs a string ending with '\0'
printStringBIOS:
    push ax
    push bx

    ; BIOS set to TTY mode
    mov ah, 0x0e

    .loopPrintString:

    ; Compare bx and `\0`
    cmp [bx], byte 0

    ; Checks equality flag, and jump to exitPrintString if equals
    je .exitPrintString
        ; Write registry
        mov al, [bx]
        ; BIOS interrupt to write the content of al
        int 0x10
        ; Increments bx to compare next character
        inc bx
        jmp .loopPrintString
    .exitPrintString:

    pop ax
    pop bx
    ret
