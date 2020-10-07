// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 09/09/2020.

#ifndef ROMAINOS_PRINTTEXT_HPP
#define ROMAINOS_PRINTTEXT_HPP

#include <types.hpp>
#include <string.hpp>

#include "rawIO.hpp"
#include "textColorModes.hpp"

namespace std::io {
    /**
     * Largeur d'une ligne VGA
     */
    const u8 VGA_WIDTH = 80;

    /**
     * Hauteur d'une colonne
     */
    const u8 VGA_HEIGHT = 25;

    /**
     * Largeur d'un tab
     */
    const u8 TAB_LENGTH = 4;

    /**
     * Set la position du curseur
     *
     * @param pos Position
     */
    void setCursorPosition(u16 pos);

    /**
     * @return Ligne curseur
     */
    u16 getCursorPositionRow();

    /**
     * @return Colonne curseur
     */
    u16 getCursorPositionCol();

    /**
     * Getter position curseur
     *
     * @return Position
     */
    u16 getCursorPosition();

    /**
     * Set la position du curseur
     *
     * @param row Ligne, -1 = dernière ligne, -2 = avant-dernière, etc
     * @param col Colonne, -1 = dernière colonne, -2 = avant-dernière, etc
     */
    void setCursorPosition(i16 row, i16 col);

    /**
     * Récupère un caractère à une position donnée
     *
     * @param pos Position
     * @return Caractère
     */
    char getChar(u16 pos);

    /**
     * Affiche un caractère
     *
     * @param c Caractère
     * @param color Couleur
     */
    void printChar(char c, uint8_t color = BG_DEFAULT | FG_DEFAULT);

    /**
     * Affiche une chaine de caractères
     *
     * @param str String
     * @param color Couleur
     */
    void printString(_In_ const char *str = "", _In_ const char* end = "\n", uint8_t color = BG_DEFAULT | FG_DEFAULT);

    /**
     * Clear l'écran VGA
     *
     * @param color Couleur
     */
    void clearScreen(uint8_t color = BG_DEFAULT | FG_DEFAULT);

    /**
     * Print int
     *
     * @tparam T Type int
     * @param value Valeur à print
     * @param end Fin de chaine
     * @param color Couleur
     */
    template <typename T>
    void printInt(T value, _In_ const char* end = "\n", uint8_t color = BG_DEFAULT | FG_DEFAULT);

    /**
     * Print float
     *
     * @tparam T Type float
     * @param value Valeur à print
     * @param end Fin de chaine
     * @param color Couleur
     */
    template <typename T>
    void printFloat(T value, _In_ const char* end = "\n", u8 decimalPlaces = 3, uint8_t color = BG_DEFAULT | FG_DEFAULT);

    /**
     * Print int hex
     *
     * @tparam T Type int
     * @param value Valeur à print
     * @param end Fin de chaine
     * @param color Couleur
     */
    template <typename T>
    void printHex(T value, _In_ const char* end = "\n", uint8_t color = BG_DEFAULT | FG_DEFAULT);
}

#include "../../../src/std/io/printText.tpp"

#endif //ROMAINOS_PRINTTEXT_HPP
