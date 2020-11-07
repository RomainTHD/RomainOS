// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 18/09/2020.

#ifndef ROMAINOS_MEMORY_H
#define ROMAINOS_MEMORY_H

#include <cstdint>

namespace stdlib {
    /**
     * Segment RAM (liste chaînée)
     */
    struct MemorySegmentHeader {
        /**
         * Taille
         */
        u64 length;

        /**
         * Segment suivant
         */
        MemorySegmentHeader* nextSegment;

        /**
         * Segment précédent
         */
        MemorySegmentHeader* prevSegment;

        /**
         * Segment libre suivant
         */
        MemorySegmentHeader* nextFreeSegment;

        /**
         * Segment libre précédent
         */
        MemorySegmentHeader* prevFreeSegment;

        /**
         * Segment libre ou non
         */
        bool isFree;
    };

    /**
     * Initialise la RAM en allouant un segment XXL qui sera ensuite découpé plus tard
     *
     * @param heapAddress Adresse du segment
     * @param heapLength Taille du segment
     */
    void initHeap(u64 heapAddress, u64 heapLength);

    /**
     * Alloue de la mémoire.
     * On est honnêtement pas sur la meilleure implémentation qui existe,
     * y a beaucoup de données inutiles pour des petites allocations à cause des infos sur les MemorySegmentHeader qu'on
     * doit bien stocker quelque part, mais ça fait le taf c'est ce qui compte.
     *
     * @param size Taille
     *
     * @return Pointeur
     */
    void* malloc(size_t size);

    /**
     * Set un tableau et le modifie
     *
     * @tparam T Type d'une case
     * @param ptr Pointeur
     * @param value Valeur
     * @param nb Nombre de cases à set
     *
     * @return Tableau
     */
    template<typename T>
    T* memset(_Out_ void* ptr, T value, size_t nb);

    /**
     * Set un tableau et le modifie
     *
     * @param ptr Pointeur
     * @param value Valeur
     * @param nb Nombre de cases à set
     *
     * @return Tableau
     */
    void* memset(_Out_ void* ptr, int value, size_t nb);

    /**
     * Mémoire initialisée à 0
     *
     * @param nb Nombre d'objets
     * @param size Taille d'un objet
     *
     * @return Pointeur
     */
    void* calloc(size_t nb, size_t size = sizeof(byte));

    /**
     * Tableau initialisé à 0
     *
     * @tparam T Type
     * @param nb Nombre de cases
     *
     * @return Pointeur
     */
    template<typename T>
    T* calloc(size_t nb);

    /**
     * Libère de la mémoire
     *
     * @param ptr Pointeur
     */
    void free(_Out_ void* ptr);

    /**
     * Réalloue de la mémoire
     *
     * @param ptr Pointeur
     * @param size Nouvelle taille
     *
     * @return Nouveau pointeur
     */
    void* realloc(_Inout_ void* ptr, size_t size);

    /**
     * Copie deux emplacements mémoire
     *
     * @param dest Destination
     * @param src Source
     * @param length Nombre d'octets
     */
    void* memcpy(_Out_ void* dest, _In_ const void* src, size_t length);

    /**
     * Copie deux emplacements mémoire
     *
     * @tparam T Type d'élément
     * @param dest Destination
     * @param src Source
     * @param length Nombre d'éléments
     */
    template <typename T>
    void* memcpy(_Out_ void* dest, _In_ const void* src, size_t length);
}

constexpr auto malloc = stdlib::malloc;
constexpr auto free = stdlib::free;

/**
 * Opérateur new
 *
 * @param size Taille
 *
 * @return Pointeur objet
 */
void* operator new(size_t size);

/**
 * Opérateur new[]
 *
 * @param size Taille
 *
 * @return Pointeur array
 */
void* operator new[](size_t size);

/**
 * Opérateur delete
 *
 * @param p Pointeur
 */
void operator delete(void* p) noexcept;

/**
 * Opérateur delete
 *
 * @param p Pointeur
 * @param size Taille
 */
void operator delete(void* p, size_t size __attribute__((unused))) noexcept;

/**
 * Opérateur delete[]
 *
 * @param p Pointeur
 */
void operator delete[](void* p) noexcept;

/**
 * Opérateur delete[]
 *
 * @param p Pointeur
 * @param size Taille
 */
void operator delete[](void* p, size_t size __attribute__((unused))) noexcept;

#include "../stdlib/memory.tpp"

#endif //ROMAINOS_MEMORY_H
