// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 10/09/2020.

#ifndef ROMAINOS_STRING_HPP
#define ROMAINOS_STRING_HPP

#include "types.hpp"

/**
 * Récupère la taille d'une string
 *
 * @param s String
 * @return Taille
 */
u32 getLength(const char* s) {
    u32 size = 0;
    const char* ptr = s;

    while (*ptr != '\0') {
        size++;
        ptr++;

        if (size == (u32) -1) {
            // throw exception
        }
    }

    return size;
}

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
    explicit string(const char* s) {
        this->_s = s;
        this->_length = getLength(s);
    }

    /**
     * Taille
     *
     * @return Taille
     */
    [[nodiscard]] u32 length() const {
        return this->_length;
    }

    /**
     * To char*
     *
     * @return Pointeur
     */
    [[nodiscard]] const char* toChar() const {
        return this->_s;
    }

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

/*

// TODO

template<typename T>
string hexToString(T value) {

}
*/

#endif //ROMAINOS_STRING_HPP
