OUTPUT_FORMAT(binary)

ENTRY(_start)

INPUT (
    extendedProgram.o
    kernel.o
    binaries.o
)

OUTPUT (
    kernel.bin
)

SECTIONS {
    . = 0x8000;

    .text : ALIGN(0x1000) {
        *(.text)
    }

    /* Pour les interruptions */
    .idt BLOCK(0x1000) : ALIGN(0x1000) {
        _idt = .;
        /* On réserve au moins 4096 bytes */
        . = . + 0x1000;
    }

    .data : ALIGN(0x1000) {
        *(.data)
    }

    /* Read-only data */
    .rodata : ALIGN(0x1000) {
        *(.rodata)
    }

    /* Uninitialized data */
    .bss : ALIGN(0x1000) {
        *(COMMON)
        *(.bss)
    }
}
