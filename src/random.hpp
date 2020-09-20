// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 18/09/2020.

#ifndef ROMAINOS_RANDOM_HPP
#define ROMAINOS_RANDOM_HPP

#include "types.hpp"

/**
 * Précision double
 */
#define RAND_DOUBLE_PRECISION 0x7fffffff

namespace std::random {
    namespace {
        /**
         * Next sous-seed pour le random
         */
        u32 next = 1;
    }

    /**
     * Random integer
     *
     * @param max Valeur max
     *
     * @return Random
     */
    u32 randint(u32 max) {
        next = next * 1103515245 + 12345;
        return (u32) (next / (max * 2)) % max;
    }

    /**
     * Seed random
     *
     * @param seed Seed
     */
    void srand(u32 seed) {
        next = seed;
    }

    /**
     * Double aléatoire dans [0;1[
     *
     * @return Double
     */
    double rand() {
        return (double) randint(RAND_DOUBLE_PRECISION) / RAND_DOUBLE_PRECISION;
    }
}

#endif //ROMAINOS_RANDOM_HPP
