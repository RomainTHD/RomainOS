// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 18/09/2020.

#ifndef ROMAINOS_MEMORY_HPP
#define ROMAINOS_MEMORY_HPP

#include "types.hpp"

namespace std::memory {
    /**
     * Alloue de la mémoire
     *
     * @param size Taille
     *
     * @return Pointeur
     */
    void* malloc(size_t size __attribute__((unused))) {
        // TODO
        return nullptr;
    }

    /**
     * Malloc mais initialise un array à 0
     *
     * @param nb Nombre d'objets
     * @param size Taille d'un objet
     *
     * @return Pointeur
     */
    void* calloc(size_t nb, size_t size) {
        return malloc(nb*size);
    }

    /**
     * Libère de la mémoire
     *
     * @param ptr Pointeur
     */
    void free(void *ptr __attribute__((unused))) {
        // TODO
    }

    /**
     * Réalloue de la mémoire
     *
     * @param ptr Pointeur
     * @param size Nouvelle taille
     *
     * @return Nouveau pointeur
     */
    void* realloc(void* ptr, size_t size) {
        free(ptr);
        return malloc(size);
    }
}

/**
 * Opérateur new
 *
 * @param size Taille
 *
 * @return Pointeur objet
 */
void* operator new(size_t size) {
    return std::memory::malloc(size);
}

/**
 * Opérateur new[]
 *
 * @param size Taille
 *
 * @return Pointeur array
 */
void* operator new[](size_t size) {
    return std::memory::malloc(size);
}

/**
 * Opérateur delete
 *
 * @param p Pointeur
 */
void operator delete(void* p) noexcept {
    std::memory::free(p);
}

/**
 * Opérateur delete
 *
 * @param p Pointeur
 * @param size Taille
 */
void operator delete(void* p, size_t size __attribute__((unused))) noexcept {
    std::memory::free(p);
}

/**
 * Opérateur delete[]
 *
 * @param p Pointeur
 */
void operator delete[](void* p) noexcept {
    std::memory::free(p);
}

/**
 * Opérateur delete[]
 *
 * @param p Pointeur
 * @param size Taille
 */
void operator delete[](void* p, size_t size __attribute__((unused))) noexcept {
    std::memory::free(p);
}

#endif //ROMAINOS_MEMORY_HPP
