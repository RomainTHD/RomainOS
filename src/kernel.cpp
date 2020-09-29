// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 08/09/2020.

#include <IO/printText.hpp>
#include <IO/IDT.hpp>
#include <memoryMap.hpp>
#include <memory.hpp>

/**
 * Point d'entrée de l'OS
 */
extern "C" void _start() {
    std::IO::clearScreen();
    std::IO::setCursorPosition(0, 0);
    std::IO::IDT::initIDT();
    std::IO::setKeyboardLayout(std::IO::AZERTY);
    std::memory::initHeap(0x100000, 0x100000);

    std::IO::printString("Tout fonctionne !\n", nullptr, BG_RED | FG_WHITE);
}
