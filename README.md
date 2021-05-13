# RomainOS

Here's a 64 bits OS, from scratch, using assembly and C++.

### How and why is it working

When booting, the BIOS will load the first 512 bytes from the disk (aka the boot sector), defined in <code>src/bootSector/bootloader.asm</code>.

The bootloader, still in "real-mode" 16-bits, will then enter in "protected-mode" 32-bits using <code>src/secondSector/extendedProgram.asm</code>.<br>
At this stage, the available memory is listed and well-structured,<br>
there's no wrap-around at 1 MB (yeah this bug really haunted me, but the A20 line is finally enabled),<br>
the interrupts are disabled, and there's a basic permission system applied, while still being limited at 4 GB.

Then, we continue up to 64-bits mode, handling a VGA display of 25x80 pixels (!).<br>
CPU infos are availables, 64 bits int are usable, GDT goes on 64 bits and the RAM finally has paging.

Then, floating points operations inside the kernel are supported using SSE.

Last assembly trick, the function <code>_start</code> from <code>src/kernel.cpp</code> is called, finally loading the "true" C++ kernel.

In C++ now, keyboards interrupts are initialized, and the available memory regions fetched.

And THEN, the kernel is ready !
