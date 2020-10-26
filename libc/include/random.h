// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 18/09/2020.

#ifndef ROMAINOS_RANDOM_H
#define ROMAINOS_RANDOM_H

#include <cstdint>

namespace random {
    /**
     * Rand max exclus
     */
    static const u64 RAND_MAX = ((u64) -1);

    /**
     * @return Random int
     */
    u64 randint();

    /**
     * Random integer
     *
     * @param max Valeur max
     *
     * @return Random
     */
    u64 randint(u64 max);

    /**
     * Double aléatoire dans [0;1[
     *
     * @return Double
     */
    double rand();

    /**
     * Random integer
     *
     * @param min Valeur min
     * @param max Valeur max
     *
     * @return Random
     */
    i32 randint(i32 min, i32 max);

    /**
     * Set seed
     *
     * @param seed Seed
     */
    void srand(u64 seed);

    /**
     * Set random seed
     */
    void srand();

    /**
     * @return Seed actuelle
     */
    u64 getSeed();
}

#endif //ROMAINOS_RANDOM_H
