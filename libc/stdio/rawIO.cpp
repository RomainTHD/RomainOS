// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 09/09/2020.

#include "rawIO.hpp"

namespace stdio {
    void outb(u16 port, byte val) {
        // Volatile pour empêcher le compilateur d'optimiser
        asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
    }

    void outw(u16 port, u16 val) {
        asm volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
    }

    byte inb(u16 port) {
        byte res;

        asm volatile ("inb %1, %0"
        : "=a"(res)
        : "Nd"(port)
        );

        return res;
    }
}
