// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 08/09/2020.

#include "IO/printText.hpp"
#include "IO/IDT.hpp"
#include "random.hpp"

/**
 * Point d'entrée de l'OS
 */
extern "C" void _start() {
    std::IO::clearScreen();
    std::IO::setCursorPosition(0, 0);
    std::IO::IDT::initIDT();
    Keyboard::setKeyboardLayout(AZERTY);
    std::IO::printString("Tout fonctionne !\n", BG_RED | FG_WHITE);
    std::IO::printInt(std::random::randint(100));
}
