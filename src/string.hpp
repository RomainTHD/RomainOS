// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 10/09/2020.

#ifndef ROMAINOS_STRING_HPP
#define ROMAINOS_STRING_HPP

#include "types.hpp"
#include "stack.hpp"

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
     * Destructeur
     */
    ~string() = default;

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

char hexToChar(byte value) {
    byte c = '\0';

    if (value <= 9) {
        c = '0' + value;
    }
    else if (value <= 15) {
        c = 'a' + (value - 10);
    }

    return (char) c;
}

template<typename T>
char* hexToString(T value, size_t minimalSize = 1) {
    Stack<byte> stack;

    while (value != 0) {
        stack.push(value % 16);
        value /= 16;
    }

    while (stack.length() < minimalSize) {
        stack.push(0);
    }

    const size_t length = stack.length();

    char str[length];

    for (size_t i=0; i<length; i++) {
        str[i] = stack.pop();
    }

    return str;
}

#endif //ROMAINOS_STRING_HPP
