// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 12/12/2020.

#ifndef ROMAINOS_EFI_MAIN_HPP
#define ROMAINOS_EFI_MAIN_HPP

#include <cstdint>

/**
 * Handle temporaire
 */
typedef void* EFI_Handle;

/**
 * Statut EFI
 */
typedef u64 EFI_Status;

/**
 * Protocole de texte in générique, WIP
 */
typedef struct EFI_TextInputProtocol {} EFI_TextInputProtocol;

/**
 * Protocole de texte out générique
 */
struct EFI_TextOutputProtocol;

// WIP
// Peut-être utile ? À voir
// typedef EFI_Status(*EFI_TextResetFunction) (struct EFI_TextOutputProtocol* self, bool extendedVerification);
// typedef EFI_Status(*EFI_TextStringFunction) (struct EFI_TextOutputProtocol* self, char16_t* string);

typedef struct EFI_TextOutputProtocol {
    /**
     * Fonction de reset
     */
    EFI_Status(*reset) (_In_ struct EFI_TextOutputProtocol* protocol, bool extendedVerification);

    /**
     * Fonction d'output
     */
    EFI_Status(*outputString) (_In_ struct EFI_TextOutputProtocol* protocol, _In_ const wchar_t* string);
} EFI_TextOutputProtocol;

/**
 * Header de table
 */
typedef struct EFI_TableHeader {
    /**
     * Signature
     */
    u64 signature;

    /**
     * Révision
     */
    u32 revision;

    /**
     * Taille du header
     */
    u32 headerSize;

    /**
     * Checksum
     */
    u32 CRC32;

    /**
     * Reserved
     */
    u32 reserved;
} EFI_TableHeader;

/**
 * System table
 */
typedef struct EFI_SystemTable {
    /**
     * Header
     */
    EFI_TableHeader header;

    /**
     * Firmware
     */
    wchar_t* firmwareVendor;

    /**
     * Version firmware
     */
    u32 firmwareVersion;

    /**
     * Handle stdin console
     */
    EFI_Handle consoleInHandle;

    /**
     * Protocole stdin
     */
    EFI_TextInputProtocol* consoleInProtocol;

    /**
     * Handle stdout console
     */
    EFI_Handle ConsoleOutHandle;

    /**
     * Protocole stdout
     */
    EFI_TextOutputProtocol* consoleOutProtocol;
} EFI_SystemTable;

#endif //ROMAINOS_EFI_MAIN_HPP
