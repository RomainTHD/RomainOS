// SPDX-License-Identifier: GPL-3.0-or-later
/**
 * Interruptions IDT (Interrupt Descriptor Tables)
 *
 * @see https://wiki.osdev.org/Interrupt_Descriptor_Table
 */
// Created by Romain on 14/09/2020.

#include <io/IDT.hpp>

/**
 * Routine assembleur keyboard
 */
extern u64 _isr1;

/**
 * IDT
 */
extern std::io::idt::IDT64 _idt[256];

/**
 * Active les IDT
 */
extern "C" void _loadIDT();

namespace std::io::idt {
    /**
     * Initialise les interruptions
     */
    void initIDT() {
        for (auto& t : _idt) {
            t.zero = 0;
            t.offsetLow = (uint16_t) (((uint64_t) &_isr1 & (uint64_t) 0x000000000000ffff));
            t.offsetMid = (uint16_t) (((uint64_t) &_isr1 & (uint64_t) 0x00000000ffff0000) >> (uint64_t) 16);
            t.offsetHigh = (uint32_t) (((uint64_t) &_isr1 & (uint64_t) 0xffffffff00000000) >> (uint64_t) 32);
            t.ist = 0;
            t.selector = 0x08;

            // Déclaré comme une interrupt gate 32 bits
            t.types_attr = 0x8e;
        }

        // remapPIC();

        // Reprogramme la puce PIC (Programmable Interface Controllers)
        outb(0x21, 0xfd);
        outb(0xa1, 0xff);

        _loadIDT();
    }

    /**
     * Gestion des interruptions clavier
     */
    extern "C" void isr1Handler() {
        // Lit depuis le port clavier
        byte b = inb(0x60);

        // Signifie au PIC que l'interruption est terminée
        outb(0x20, 0x20);
        outb(0xa0, 0x20);

        std::io::handleEvent(b);
    }
}
