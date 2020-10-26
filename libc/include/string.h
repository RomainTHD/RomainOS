// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 10/09/2020.

#ifndef ROMAINOS_STRING_HPP
#define ROMAINOS_STRING_HPP

#include <stdint.h>
#include <stack>

/**
 * Récupère la taille d'une string
 *
 * @param s String
 * @return Taille
 */
u32 getLength(const char* s);

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
const char* hexToString(T value);

/**
 * Int vers string
 *
 * @tparam T Type
 * @param value Int
 *
 * @return String de l'int
 */
template<typename T>
const char* intToString(T value);

/**
 * Hack pour utiliser intToString sur des pointeurs.
 * Le <code>value *= -1;</code> ne passe en effet pas pour des pointeurs.
 *
 * @tparam T Type
 * @param value Int*
 *
 * @return String de l'int
 */
template<typename T>
const char* intToString(T* value);

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
const char* floatToString(T value, u8 decimalPlaces = 3);

#include "../string/string.tpp"

#endif //ROMAINOS_STRING_HPP
