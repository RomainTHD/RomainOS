// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 09/09/2020.

#ifndef ROMAINOS_PRINTTEXT_HPP
#define ROMAINOS_PRINTTEXT_HPP

#include "types.hpp"
#include "IO.hpp"
#include "string.hpp"

/**
 * Emplacement VRAM
 */
#define VGA_MEMORY (byte*) 0xb8000

/**
 * Largeur d'une ligne VGA
 */
#define VGA_WIDTH 80

/**
 * Hauteur d'une colonne
 */
#define VGA_HEIGHT 25

/**
 * Largeur d'un tab
 */
#define TAB_LENGTH 4

/**
 * Position du curseur
 */
u16 cursorPosition = 0;

/**
 * Set la position du curseur
 *
 * @param pos Position
 */
void setCursorPosition(u16 pos) {
    pos %= (VGA_WIDTH * VGA_HEIGHT);

    outb(0x3d4, 0x0f);
    outb(0x3d5, (byte)(pos & 0xff));
    outb(0x3d4, 0x0e);
    outb(0x3d5, (byte)((pos >> 8) & 0xff));

    cursorPosition = pos;
}

/**
 * Set la position du curseur
 *
 * @param row Ligne, -1 = dernière ligne, -2 = avant-dernière, etc
 * @param col Colonne, -1 = dernière colonne, -2 = avant-dernière, etc
 */
void setCursorPosition(i16 row, i16 col) {
    if (row < 0) {
        row = (row + VGA_HEIGHT) % VGA_HEIGHT;
    }

    if (col < 0) {
        col = (col + VGA_WIDTH) % VGA_WIDTH;
    }

    setCursorPosition(VGA_WIDTH*row + col);
}

/**
 * Affiche une chaine de caractères
 *
 * @param str String
 */
void printString(const char* str) {
    byte* charPtr = (byte*) str;
    u16 index = cursorPosition;

    while (*charPtr != '\0') {
        switch (*charPtr) {
            case '\n':
                index += VGA_WIDTH;
                [[fallthrough]]; // En cas de '\n' on veut aussi revenir à la ligne
            case '\r':
                index -= index % VGA_WIDTH;
                break;

            case '\t':
                for (u8 i=0; i < (u8) (index % VGA_WIDTH) % TAB_LENGTH; i++) {
                    *(VGA_MEMORY + index*2) = ' ';
                    index++;
                }
                break;

            default:
                *(VGA_MEMORY + index*2) = *charPtr;
                index++;
                break;
        }

        charPtr++;
    }

    setCursorPosition(index);
}

#endif //ROMAINOS_PRINTTEXT_HPP
