// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 21/09/2020.

#ifndef ROMAINOS_MEMORYMAP_HPP
#define ROMAINOS_MEMORYMAP_HPP

#include <types.hpp>
#include <io/IO.hpp>

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
    u8 getMemoryRegionCount();

    /**
     * @return Nombre de régions utilisables
     */
    u8 getNumberOfUsableMemoryRegions();

    /**
     * @return Régions utilisables
     */
    MemoryMapEntry** getUsableMemoryRegions();

    /**
     * Affiche une région
     *
     * @param entry Memory map entry
     */
    void printMemoryMap(_In_ const MemoryMapEntry* entry);

    /**
     * Affiche toutes les régions
     */
    void printAllMemoryMapEntries();

    /**
     * Affiche toutes les régions utilisables
     */
    void printUsableMemoryMapEntries();
}

#endif //ROMAINOS_MEMORYMAP_HPP
