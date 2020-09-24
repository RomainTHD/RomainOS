// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 08/09/2020.

#include "IO/printText.hpp"
#include "IO/IDT.hpp"
#include "memoryMap.hpp"

/**
 * Point d'entrée de l'OS
 */
extern "C" void _start() {
    std::IO::clearScreen();
    std::IO::setCursorPosition(0, 0);
    std::IO::IDT::initIDT();
    std::IO::setKeyboardLayout(std::IO::AZERTY);

    /*
    for (u8 i=0; i<std::memory::getMemoryRegionCount(); i++) {
        std::memory::MemoryMapEntry* entry = (std::memory::MemoryMapEntry*) 0x5000;
        entry += i;
        std::memory::printMemoryMap(entry);
        std::IO::printString();
    }
    /*/
    std::memory::MemoryMapEntry** usableMemoryMap = std::memory::getUsableMemoryRegions();

    for (u8 i=0; i<std::memory::getNumberOfUsableMemoryRegions(); i++) {
        std::memory::MemoryMapEntry* entry = usableMemoryMap[i];
        std::memory::printMemoryMap(entry);
        std::IO::printString();
    }
    //*/

    std::IO::printString("Tout fonctionne !\n", BG_RED | FG_WHITE);
}
