// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 07/11/2020.

#ifndef ROMAINOS_STRINGCLASS_HPP
#define ROMAINOS_STRINGCLASS_HPP

#include <stdint.h>

/**
 * String
 */
class string {
public:
    string() = delete;

    /**
     * Constructeur
     *
     * @param s Chaine
     */
    explicit string(const char* s);

    /**
     * Destructeur
     */
    ~string() = default;

    /**
     * Taille
     *
     * @return Taille
     */
    [[nodiscard]] u32 length() const;

    /**
     * To char*
     *
     * @return Pointeur
     */
    [[nodiscard]] const char* toChar() const;

private:
    /**
     * Chaine
     */
    const char* _s;

    /**
     * Taille
     */
    u32 _length;
};

#endif //ROMAINOS_STRINGCLASS_HPP
