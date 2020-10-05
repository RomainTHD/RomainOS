// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 04/10/2020.

#include <io/IO.hpp>

int main() {
    std::io::keyboard::setKeyboardLayout(std::io::keyboard::AZERTY);
    std::io::keyboard::addEventHandler([](std::io::keyboard::KeyEvent e){
        std::io::printChar(e.key);
    });

    std::io::printString("Tout fonctionne !", "\n", BG_RED | FG_WHITE);
    return 0;
}
