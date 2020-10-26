// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 05/10/2020.

#ifndef ROMAINOS_PRINTTEXT_TPP
#define ROMAINOS_PRINTTEXT_TPP

namespace stdio {
    template <typename T>
    void printInt(T value, _In_ const char* end, uint8_t color) {
        printString(intToString(value), end, color);
    }

    template <typename T>
    void printFloat(T value, _In_ const char* end, u8 decimalPlaces, uint8_t color) {
        printString(floatToString(value, decimalPlaces), end, color);
    }

    template <typename T>
    void printHex(T value, _In_ const char* end, uint8_t color) {
        printString(hexToString(value), end, color);
    }
}

#endif //ROMAINOS_PRINTTEXT_TPP
