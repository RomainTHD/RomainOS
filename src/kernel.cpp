// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 08/09/2020.

#include "IO/printText.hpp"
#include "IO/IDT.hpp"

/**
 * Point d'entrée de l'OS
 */
extern "C" void _start() {
    clearScreen();
    setCursorPosition(0, 0);
    initIDT();
    Keyboard::setKeyboardLayout(AZERTY);
    printString("Tout fonctionne !", BG_RED | FG_WHITE);
}
