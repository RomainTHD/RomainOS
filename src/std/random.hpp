// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 18/09/2020.

#ifndef ROMAINOS_RANDOM_HPP
#define ROMAINOS_RANDOM_HPP

#include <types.hpp>

/**
 * Rand max exclus
 */
#define _RAND_MAX ((u64) -1)

/**
 * Random seed
 *
 * @param seed Seed
 */
extern "C" void _srands(u64 seed);

/**
 * Random seed
 */
extern "C" void _srand();

/**
 * Random int
 */
extern "C" u64 _randint();

/**
 * Get seed
 */
extern "C" u64 _getSeed();

namespace std::random {
    /**
     * @return Random int
     */
    u64 randint() {
        return _randint();
    }

    /**
     * Random integer
     *
     * @param max Valeur max
     *
     * @return Random
     */
    u64 randint(u64 max) {
        return randint() % max;
    }

    /**
     * Double aléatoire dans [0;1[
     *
     * @return Double
     */
    double rand() {
        return (double) randint() / (double) _RAND_MAX;
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
        return min + rand() * (double) (max - min);
    }

    /**
     * Set seed
     *
     * @param seed Seed
     */
    void srand(u64 seed) {
        _srands(seed);
    }

    /**
     * Set random seed
     */
    void srand() {
        _srand();
    }

    u64 getSeed() {
        return _getSeed();
    }
}

#undef _RAND_MAX

#endif //ROMAINOS_RANDOM_HPP
