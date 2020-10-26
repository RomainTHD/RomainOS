// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 26/09/2020.

#include "system.hpp"

extern "C" void _exit();

namespace std::system {
    void shutdown() {
        stdio::outw(0x604, 0x2000); // Qemu
        stdio::outw(0x4004, 0x3400); // VBox
        stdio::outw(0xB004, 0x2000); // Boshs

        _exit();
    }

    void shutdownAndPrint() {
        stdio::setCursorPosition(-1, 0);
        stdio::printString("Fin du programme...");

        time::sleep(1);

        shutdown();

        stdio::setCursorPosition(-1, 0);
        stdio::printString("Erreur lors de la sortie de l'emulateur !");
        time::sleep(1);
    }
}
