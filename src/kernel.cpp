// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 08/09/2020.

#include "IO/printText.hpp"

extern "C" void _start() {
    clearScreen();
    printString("OK :)");
}
