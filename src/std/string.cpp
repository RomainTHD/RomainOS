// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 10/09/2020.

#include <string.hpp>

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
