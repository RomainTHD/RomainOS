OUTPUT_FORMAT(binary)

ENTRY(_start)

INPUT (
    ./obj/binaries.o
    ./obj/extendedProgram.o
    ./obj/kernel/icxxabi.o
    ./obj/kernel/IDT.o
    ./obj/kernel/kernel.o
    ./obj/kernel/system.o
    ./obj/libc/random.o
    ./obj/libc/time.o
    ./obj/libc/stddef/types.o
    ./obj/libc/stdio/keyboard.o
    ./obj/libc/stdio/keyboardLayout.o
    ./obj/libc/stdio/printText.o
    ./obj/libc/stdio/rawIO.o
    ./obj/libc/stdlib/memory.o
    ./obj/libc/stdlib/memoryMap.o
    ./obj/libc/string/stringC.o
    ./obj/libc/string/stringClass.o
    ./obj/programs/textEditor/textEditor.o
)

OUTPUT (
    ./bin/part/kernel.bin
)

SECTIONS {
    /* Section start */
    . = 0x8000;

    .text : ALIGN(0x1000) {
        *(.text)
        *(.rodata*)
    }

    /* Interrupts */
    .idt BLOCK(0x1000) : ALIGN(0x1000) {
        _idt = .;
        /* At least 4096 bytes reserved */
        . = . + 0x1000;
    }

    /* Read-only data */
    .rodata : ALIGN(0x1000) {}

    /* Read-write initialized data */
    .data : ALIGN(0x1000) {
        *(.data)
    }

    /* Read-write uninitialized data + stack */
    .bss : ALIGN(0x1000) {
        *(COMMON)
        *(.bss)
    }
}
