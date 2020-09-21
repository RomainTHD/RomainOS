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

/**
 * Hex to String
 *
 * @tparam T Type
 * @param value Valeur
 *
 * @return Hex
 */
template<typename T>
const char* hexToString(T value) {
    static char hexToStringOutput[128];
    T* valPtr = &value;
    u8* ptr;
    u8 temp;

    /**
     * Pour même taille entre 0b00000000 et 0b11111111 par exemple
     */
    u8 size = ((sizeof(T)) * 2 - 1);

    for (u8 i = 0; i < size; i++) {
        ptr = ((u8 *)valPtr + i);
        temp = ((*ptr & 0xf0) >> 4);
        hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
        temp = ((*ptr & 0x0f));
        hexToStringOutput[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
    }

    hexToStringOutput[size + 1] = 0;

    return hexToStringOutput;
}

/**
 * Int vers string
 *
 * @tparam T Type
 * @param value Int
 *
 * @return String de l'int
 */
template<typename T>
const char* intToString(T value) {
    bool isNegative = false;

    if (value < 0) {
        isNegative = true;
        value *= -1;
    }

    static char integerToStringOutput[128];
    u8 size = 0;
    u64 sizeTester = (u64) value;
    u8 index = 0;

    while (sizeTester / 10 > 0) {
        sizeTester /= 10;
        size++;
    }

    if (isNegative) {
        size++;
    }

    u64 newValue = (u64) value;
    while (newValue / 10 > 0) {
        u8 remainder = newValue % 10;
        newValue /= 10;
        integerToStringOutput[size - index] = (char) (remainder + '0');
        index++;
    }

    u8 remainder = newValue % 10;
    integerToStringOutput[size - index] = (char) (remainder + '0');
    index++;

    if (isNegative == 1) {
        integerToStringOutput[size - index] = '-';
    }
    integerToStringOutput[size + 1] = '\0';

    return integerToStringOutput;
}

/**
 * Float to string
 *
 * @tparam T Type
 * @param value Value
 * @param decimalPlaces Nb de décimales
 *
 * @return String de float
 */
template <typename T>
const char* floatToString(T value, u8 decimalPlaces = 3) {
    static char floatToStringOutput[128];
    char *intPtr = (char*) intToString((int) value);
    char *floatPtr = floatToStringOutput;

    if (value < 0) {
        value *= -1;
    }

    while (*intPtr != '\0') {
        *floatPtr = *intPtr;

        floatPtr++;
        intPtr++;
    }

    *floatPtr = '.';
    floatPtr++;

    T newValue = value - (int) value;

    for (u8 i = 0; i < decimalPlaces; i++) {
        newValue *= 10;
        *floatPtr = (char) newValue + '0';
        floatPtr++;
        newValue = newValue - (int) newValue;
    }

    *floatPtr = '\0';

    return floatToStringOutput;
}

#endif //ROMAINOS_STRING_HPP
