// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 26/09/2020.

#ifndef ROMAINOS_SYSTEM_HPP
#define ROMAINOS_SYSTEM_HPP

#include <io/rawIO.hpp>
#include <io/printText.hpp>
#include <time.hpp>

extern "C" void _exit();

namespace std::system {
    /**
     * Shutdown
     */
    void shutdown() {
        std::io::outw(0x604, 0x2000); // Qemu
        std::io::outw(0x4004, 0x3400); // VBox
        std::io::outw(0xB004, 0x2000); // Boshs

        _exit();
    }

    /**
     * Shutdown avec un message
     */
    void shutdownAndPrint() {
        std::io::setCursorPosition(-1, 0);
        std::io::printString("Fin du programme...");

        std::time::sleep(1);

        shutdown();

        std::io::setCursorPosition(-1, 0);
        std::io::printString("Erreur lors de la sortie de l'emulateur !");
        std::time::sleep(1);
    }
}

#endif //ROMAINOS_SYSTEM_HPP
