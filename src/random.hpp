// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 18/09/2020.

#ifndef ROMAINOS_RANDOM_HPP
#define ROMAINOS_RANDOM_HPP

#include "types.hpp"

/**
 * Rand max exclus
 */
#define _RAND_MAX 32768

namespace std::random {
    namespace {
        /**
         * Next sous-seed pour le random
         */
        u32 _next = 1;

        /**
         * Fonction random comme définie dans la bibliothèque C
         *
         * @return Nb random entre 0 inclus et 32768 exclus
         */
        u32 _randint() {
            _next = _next * 1103515245 + 12345;
            return (u32) (_next / (_RAND_MAX * 2)) % _RAND_MAX;
        }
    }

    /**
     * Double aléatoire dans [0;1[
     *
     * @return Double
     */
    double rand() {
        return (double) _randint() / (double) _RAND_MAX;
    }

    /**
     * Random integer
     *
     * @param max Valeur max
     *
     * @return Random
     */
    u32 randint(u32 max) {
        return rand() * max;
    }

    /**
     * Random integer
     *
     * @param min Valeur min
     * @param max Valeur max
     *
     * @return Random
     */
    i32 randint(i32 min, i32 max) {
        return min + rand() * (max - min);
    }

    /**
     * Seed random
     *
     * @param seed Seed
     */
    void srand(u32 seed) {
        _next = seed;
    }
}

#undef _RAND_MAX

#endif //ROMAINOS_RANDOM_HPP
