// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 07/11/2020.

#ifndef ROMAINOS_STRINGROMAINOS_HPP
#define ROMAINOS_STRINGROMAINOS_HPP

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

#include "../string/stringRomainOS.tpp"

#endif //ROMAINOS_STRINGROMAINOS_HPP
