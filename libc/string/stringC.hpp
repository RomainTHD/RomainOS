// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 07/11/2020.

#ifndef ROMAINOS_STRINGC_HPP
#define ROMAINOS_STRINGC_HPP

#include <memory.h>

namespace stdstring {
    /**
     * Compare deux string
     *
     * @param a String 1
     * @param b String 2
     *
     * @return 0 si a == b, -1 si a < b, 1 si a > b
     */
    int strcmp(const char* a, const char* b);

    /**
     * Calcule la taille d'une chaîne
     *
     * @param str String
     *
     * @return Taille
     */
    u32 strlen(const char* str);

    /**
     * Duplique une chaine en effectuant un malloc
     *
     * @param str Chaine
     *
     * @return Taille
     */
    char* strdup(const char* str);

    /**
     * Copie une chaine
     *
     * @param dest Destination
     * @param src Source
     *
     * @return Chaine copiée
     */
    char* strcpy(char* dest, const char* src);
}

#endif //ROMAINOS_STRINGC_HPP
