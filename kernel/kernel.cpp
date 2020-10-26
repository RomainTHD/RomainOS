// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 08/09/2020.

#include <cstdlib>
#include <cstdio>

#include "IDT.hpp"
#include "system.hpp"

extern int main();

/**
 * Point d'entrée de l'OS
 */
extern "C" void _start() {
    stdio::clearScreen();
    stdio::setCursorPosition(0, 0);
    idt::initIDT();
    stdlib::initHeap(0x100000, 0x100000);

    stdio::keyboard::addEventHandler([](stdio::keyboard::KeyEvent e) {
        if (e.keyCode == stdio::keyboard::VK_ESC) {
            std::system::shutdownAndPrint();
        }
    });

    main();
}
