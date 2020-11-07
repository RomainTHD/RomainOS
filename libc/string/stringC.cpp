// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 10/09/2020.

#include "stringC.hpp"

namespace stdstring {
    int strcmp(const char* a, const char* b) {
        u32 i = 0;
        while (true) {
            if (a[i] < b[i]) {
                return -1;
            }
            else if (a[i] > b[i]) {
                return 1;
            }
            else {
                if (a[i] == '\0') {
                    return 0;
                }
                ++i;
            }
        }
    }

    u32 strlen(const char* str) {
        u32 i = 0;
        while (str[i] != '\0') {
            ++i;
        }
        return i;
    }

    char* strdup(const char* str) {
        int len = strlen(str);
        return (char*) stdlib::memcpy(malloc(sizeof(char) * (len + 1)), str, len + 1);;
    }

    char* strcpy(char* dest, const char* src) {
        return (char*) stdlib::memcpy(dest, src, strlen(src) + 1);
    }
}
