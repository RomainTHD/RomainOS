// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 12/12/2020.

#include "efi_main.hpp"

extern "C" {
    /**
     * Point d'entrée boot EFI
     *
     * @param ImageHandle
     * @param SystemTable Table système
     *
     * @return Status
     */
    [[noreturn]]
    [[maybe_unused]]
    EFI_Status efiMain([[maybe_unused]] EFI_Handle ImageHandle, EFI_SystemTable* SystemTable) {
        // EFI blablabla donc les strings ne sont pas des `const char*` mais des `const wchar_t*`,
        // aka des `const char16_t*`, d'où le `L"..."`
        SystemTable->consoleOutProtocol->outputString(SystemTable->consoleOutProtocol, L"OK\n\r");
        while (true);
        // Pas de return parce que `[[noreturn]]` et `while (true);`
    }
}
