// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 21/09/2020.

#include <memoryMap.hpp>

/**
 * Nombre de régions
 */
extern u8 _memoryRegionCount;

namespace std::memory {
    u8 getMemoryRegionCount() {
        return _memoryRegionCount;
    }

    u8 getNumberOfUsableMemoryRegions() {
        return _usableRegionsIndex;
    }

    MemoryMapEntry** getUsableMemoryRegions() {
        if (!_memoryRegionsCalculated) {
            _memoryRegionsCalculated = true;

            for (u8 i = 0; i < _memoryRegionCount; i++) {
                MemoryMapEntry* entry = (MemoryMapEntry*) 0x5000;
                entry += i;

                if (entry->regionType == 1) {
                    _usableMemoryRegions[_usableRegionsIndex] = entry;
                    _usableRegionsIndex++;
                }
            }
        }

        return _usableMemoryRegions;
    }

    void printMemoryMap(_In_ const MemoryMapEntry* entry) {
        std::io::printString("Memory base: \t\t", "");
        std::io::printInt(entry->baseAddress);

        std::io::printString("Memory length: \t\t", "");
        std::io::printInt(entry->regionLength);

        std::io::printString("Memory type: \t\t", "");
        std::io::printHex(entry->regionType);

        std::io::printString("Memory attributes: \t", "");
        std::io::printHex(entry->extendedAttributes);
    }

    void printAllMemoryMapEntries() {
        for (u8 i=0; i<std::memory::getMemoryRegionCount(); i++) {
            std::memory::MemoryMapEntry* entry = (std::memory::MemoryMapEntry*) 0x5000;
            entry += i;
            std::memory::printMemoryMap(entry);
            std::io::printString();
        }
    }

    void printUsableMemoryMapEntries() {
        std::memory::MemoryMapEntry** usableMemoryMap = std::memory::getUsableMemoryRegions();

        for (u8 i=0; i<std::memory::getNumberOfUsableMemoryRegions(); i++) {
            std::memory::MemoryMapEntry* entry = usableMemoryMap[i];
            std::memory::printMemoryMap(entry);
            std::io::printString();
        }
    }
}
