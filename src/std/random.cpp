// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 18/09/2020.

#include <random.hpp>

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
    u64 randint() {
        return _randint();
    }

    u64 randint(u64 max) {
        return randint() % max;
    }

    double rand() {
        return (double) randint() / (double) RAND_MAX;
    }

    i32 randint(i32 min, i32 max) {
        return min + rand() * (double) (max - min);
    }

    void srand(u64 seed) {
        _srands(seed);
    }

    void srand() {
        _srand();
    }

    u64 getSeed() {
        return _getSeed();
    }
}
