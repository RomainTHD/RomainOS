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
         */
        u32 regionType;

        /**
         * Attributs
         */
        u32 extendedAttributes;
    };

    u8 getMemoryRegionCount() {
        return _memoryRegionCount;
    }
}

#endif //ROMAINOS_MEMORYMAP_HPP
