// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 09/09/2020.

#include <io/printText.hpp>

namespace std::io {
    namespace {
        /**
         * Position du curseur
         */
        u16 _cursorPosition = 0;
    }

    void setCursorPosition(u16 pos) {
        pos %= (VGA_WIDTH * VGA_HEIGHT);

        std::io::outb(0x3d4, 0x0f);
        std::io::outb(0x3d5, (byte) (pos & (u16) 0xff));
        std::io::outb(0x3d4, 0x0e);
        std::io::outb(0x3d5, (byte) ((u16) (pos >> (u16) 8) & (u16) 0xff));

        _cursorPosition = pos;
    }

    u16 getCursorPosition() {
        return _cursorPosition;
    }

    void setCursorPosition(i16 row, i16 col) {
        if (row < 0) {
            row = (row + VGA_HEIGHT) % VGA_HEIGHT;
        }

        if (col < 0) {
            col = (col + VGA_WIDTH) % VGA_WIDTH;
        }

        setCursorPosition(VGA_WIDTH * row + col);
    }

    void printChar(char c, uint8_t color) {
        switch (c) {
            case '\0':
                break;

            case '\n':
                setCursorPosition(getCursorPosition() + VGA_WIDTH);
                [[fallthrough]]; // En cas de '\n' on veut aussi revenir à la ligne
            case '\r':
                setCursorPosition(getCursorPosition() - (getCursorPosition() % VGA_WIDTH));
                break;

            case '\t': {
                u8 i = 0;
                do {
                    printChar(' ');
                    i++;
                } while (i <= (u8) (getCursorPosition() % VGA_WIDTH) % TAB_LENGTH);
            }
                break;

            case 0x7f:
                // DEL
                break;

            default:
                if (c >= 0x20 && c < 0x7f) {
                    // de ' ' à DEL (exclus)
                    *(VGA_MEMORY + getCursorPosition() * 2) = c;
                    *(VGA_MEMORY + getCursorPosition() * 2 + 1) = color;
                    setCursorPosition(getCursorPosition() + 1);
                }
        }
    }

    void printString(_In_ const char *str, _In_ const char* end, uint8_t color) {
        if (str == nullptr) {
            u16 c = getCursorPosition();
            setCursorPosition(-1, -1);
            printChar('*', color);
            setCursorPosition(c);
        }
        else {
            byte* charPtr = (byte*) str;

            while (*charPtr != '\0') {
                printChar(*charPtr, color);
                charPtr++;
            }

            if (end != nullptr) {
                charPtr = (byte *) end;
                while (*charPtr != '\0') {
                    printChar(*charPtr, color);
                    charPtr++;
                }
            }
        }
    }

    void clearScreen(uint8_t color) {
        // Fonctionne toujours
        /*
        uint64_t value = 0;
        value += (uint64_t) color << 8;
        value += (uint64_t) color << 24;
        value += (uint64_t) color << 40;
        value += (uint64_t) color << 56;

        for (uint64_t *i = (u64 *)VGA_MEMORY; i < (u64 *)(VGA_MEMORY + 4000); i++) {
            *i = value;
        }
         */

        // Fonctionne ssi setCursorPosition loop à 0

        setCursorPosition(0);

        do {
            printChar(' ', color);
        } while (getCursorPosition() != 0);
    }

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

    template void printInt(int value, _In_ const char* end, uint8_t color);
    template void printInt(u32 value, _In_ const char* end, uint8_t color);
    template void printInt(u64 value, _In_ const char* end, uint8_t color);

    template void printHex(u32 value, _In_ const char* end, uint8_t color);
}
