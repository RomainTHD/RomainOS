// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 21/09/2020.

#include "memoryMap.hpp"

/**
 * Nombre de régions
 */
extern u8 _memoryRegionCount;

namespace stdlib {
    namespace {
        /**
         * Liste des régions
         */
        MemoryMapEntry* _usableMemoryRegions[10];

        /**
         * Régions déjà calculées ou non
         */
        bool _memoryRegionsCalculated = false;

        /**
         * Index des régions utilisables
         */
        u8 _usableRegionsIndex = 0;
    }

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
        stdio::printString("Memory base: \t\t", "");
        stdio::printInt(entry->baseAddress);

        stdio::printString("Memory length: \t\t", "");
        stdio::printInt(entry->regionLength);

        stdio::printString("Memory type: \t\t", "");
        stdio::printHex(entry->regionType);

        stdio::printString("Memory attributes: \t", "");
        stdio::printHex(entry->extendedAttributes);
    }

    void printAllMemoryMapEntries() {
        for (u8 i = 0; i < getMemoryRegionCount(); i++) {
            MemoryMapEntry* entry = (MemoryMapEntry*) 0x5000;
            entry += i;
            printMemoryMap(entry);
            stdio::printString();
        }
    }

    void printUsableMemoryMapEntries() {
        MemoryMapEntry** usableMemoryMap = getUsableMemoryRegions();

        for (u8 i = 0; i < getNumberOfUsableMemoryRegions(); i++) {
            MemoryMapEntry* entry = usableMemoryMap[i];
            printMemoryMap(entry);
            stdio::printString();
        }
    }
}
