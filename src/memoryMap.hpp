// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 21/09/2020.

#ifndef ROMAINOS_MEMORYMAP_HPP
#define ROMAINOS_MEMORYMAP_HPP

#include "types.hpp"

extern u8 _memoryRegionCount;

namespace std::memory {
    /**
     * Entrée du listing de la mémoire
     */
    struct MemoryMapEntry {
        /**
         * Adresse de base
         */
        u64 baseAddress;

        /**
         * Taille de la région
         */
        u64 regionLength;

        /**
         * Type de région
         *
         * 1: normale, utilisable
         * 2: réservée, inutilisable
         * 3: réclamable ACPI
         * 4: ACPI NVS
         * 5: région contenant de la bad memory
         */
        u32 regionType;

        /**
         * Attributs
         *
         * Bit 0: doit être ignoré (si 0) ou non
         * Bit 1: non-volatile (si 1)
         */
        u32 extendedAttributes;
    };

    namespace {
        MemoryMapEntry* usableMemoryRegions[10];
        bool memoryRegionsCalculated = false;
        u8 usableRegionsIndex = 0;
    }

    u8 getMemoryRegionCount() {
        return _memoryRegionCount;
    }

    u8 getNumberOfUsableMemoryRegions() {
        return usableRegionsIndex;
    }

    MemoryMapEntry** getUsableMemoryRegions() {
        if (!memoryRegionsCalculated) {
            memoryRegionsCalculated = true;

            for (u8 i = 0; i < _memoryRegionCount; i++) {
                MemoryMapEntry* entry = (MemoryMapEntry*) 0x5000;
                entry += i;

                if (entry->regionType == 1) {
                    usableMemoryRegions[usableRegionsIndex] = entry;
                    usableRegionsIndex++;
                }
            }
        }

        return usableMemoryRegions;
    }

    void printMemoryMap(MemoryMapEntry* entry) {
        std::IO::printString("Memory base: \t\t");
        std::IO::printInt(entry->baseAddress);

        std::IO::printString("Memory length: \t\t");
        std::IO::printInt(entry->regionLength);

        std::IO::printString("Memory type: \t\t");
        std::IO::printHex(entry->regionType);

        std::IO::printString("Memory attributes: \t");
        std::IO::printHex(entry->extendedAttributes);
    }
}

#endif //ROMAINOS_MEMORYMAP_HPP
