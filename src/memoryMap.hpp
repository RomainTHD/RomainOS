// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 21/09/2020.

#ifndef ROMAINOS_MEMORYMAP_HPP
#define ROMAINOS_MEMORYMAP_HPP

#include "types.hpp"

/**
 * Nombre de régions
 */
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

    /**
     * @return Nombre de régions RAM
     */
    u8 getMemoryRegionCount() {
        return _memoryRegionCount;
    }

    /**
     * @return Nombre de régions utilisables
     */
    u8 getNumberOfUsableMemoryRegions() {
        return _usableRegionsIndex;
    }

    /**
     * @return Régions utilisables
     */
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

    /**
     * Affiche une région
     *
     * @param entry Memory map entry
     */
    void printMemoryMap(MemoryMapEntry* entry) {
        std::IO::printString("Memory base: \t\t", "");
        std::IO::printInt(entry->baseAddress);

        std::IO::printString("Memory length: \t\t", "");
        std::IO::printInt(entry->regionLength);

        std::IO::printString("Memory type: \t\t", "");
        std::IO::printHex(entry->regionType);

        std::IO::printString("Memory attributes: \t", "");
        std::IO::printHex(entry->extendedAttributes);
    }

    /**
     * Affiche toutes les régions
     */
    void printAllMemoryMapEntries() {
        for (u8 i=0; i<std::memory::getMemoryRegionCount(); i++) {
            std::memory::MemoryMapEntry* entry = (std::memory::MemoryMapEntry*) 0x5000;
            entry += i;
            std::memory::printMemoryMap(entry);
            std::IO::printString();
        }
    }

    /**
     * Affiche toutes les régions utilisables
     */
    void printUsableMemoryMapEntries() {
        std::memory::MemoryMapEntry** usableMemoryMap = std::memory::getUsableMemoryRegions();

        for (u8 i=0; i<std::memory::getNumberOfUsableMemoryRegions(); i++) {
            std::memory::MemoryMapEntry* entry = usableMemoryMap[i];
            std::memory::printMemoryMap(entry);
            std::IO::printString();
        }
    }
}

#endif //ROMAINOS_MEMORYMAP_HPP
