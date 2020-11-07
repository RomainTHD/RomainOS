// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 07/11/2020.

#ifndef ROMAINOS_MEMORY_TPP
#define ROMAINOS_MEMORY_TPP

namespace stdlib {
    template<typename T>
    T* memset(_Out_ void* ptr, T value, size_t nb) {
        for (u64 i=0; i<nb; i++) {
            ((T*) ptr)[i] = value;
        }
        return (T*) ptr;
    }

    template<typename T>
    T* calloc(size_t nb) {
        return memset<T>(malloc(nb*sizeof(T)), 0, nb);
    }

    template <typename T>
    void* memcpy(_Out_ void* dest, _In_ const void* src, size_t length) {
        for (u64 i=0; i<length; i++) {
            ((T*) dest)[i] = ((T*) src)[i];
        }
        return dest;
    }
}

#endif //ROMAINOS_MEMORY_TPP
