// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 08/09/2020.

#include <io/printText.hpp>
#include <io/IDT.hpp>
#include <io/IO.hpp>
#include <memory.hpp>

extern int main();

/**
 * Point d'entrée de l'OS
 */
extern "C" void _start() {
    std::io::clearScreen();
    std::io::setCursorPosition(0, 0);
    std::io::idt::initIDT();
    std::memory::initHeap(0x100000, 0x100000);

    std::io::keyboard::addEventHandler([](std::io::keyboard::KeyEvent e) {
        if (e.keyCode == std::io::keyboard::VK_ESC) {
            std::system::shutdownAndPrint();
        }
    });

    main();
}
