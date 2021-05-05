// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 04/10/2020.

#include <cstdio>

int main() {
    stdio::keyboard::setKeyboardLayout(stdio::keyboard::AZERTY);
    stdio::keyboard::addEventHandler([](stdio::keyboard::KeyEvent e) {
        stdio::printChar(e.key);
    });

    stdio::printString("Everything works fine !", "\n", stdio::BG_RED | stdio::FG_WHITE);
    return 0;
}
