// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 09/09/2020.

#ifndef ROMAINOS_PRINTTEXT_HPP
#define ROMAINOS_PRINTTEXT_HPP

#include "types.hpp"
#include "IO.hpp"

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
 * Position du curseur
 */
u16 cursorPosition;

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

void setCursorPosition(i16 row, i16 col) {
    if (row < 0) {
        row = (row + VGA_HEIGHT) % VGA_HEIGHT;
    }

    if (col < 0) {
        col = (col + VGA_WIDTH) % VGA_WIDTH;
    }

    setCursorPosition(VGA_WIDTH*row + col);
}

#endif //ROMAINOS_PRINTTEXT_HPP
