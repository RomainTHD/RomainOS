// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 18/09/2020.

#ifndef ROMAINOS_MEMORY_HPP
#define ROMAINOS_MEMORY_HPP

#include <types.hpp>

namespace std::memory {
    namespace {
        /**
         * Segment RAM (liste chaînée)
         */
        struct MemorySegment {
            /**
             * Taille
             */
            u64 length;

            /**
             * Segment suivant
             */
            MemorySegment* nextSegment;

            /**
             * Segment précédent
             */
            MemorySegment* prevSegment;

            /**
             * Segment libre suivant
             */
            MemorySegment* nextFreeSegment;

            /**
             * Segment libre précédent
             */
            MemorySegment* prevFreeSegment;

            /**
             * Segment libre ou non
             */
            bool isFree;
        };

        /**
         * Combine deux segments libres et évite la fragmentation
         *
         * @param segA Segment A
         * @param segB Segment B
         */
        void combineFreeSegments(_Inout_ MemorySegment* segA, _Inout_ MemorySegment* segB) {
            if (segA == nullptr) {
                return;
            }

            if (segB == nullptr) {
                return;
            }

            if (segA < segB) {
                segA->length += segB->length + sizeof(MemorySegment);
                segA->nextSegment = segB->nextSegment;
                segA->nextFreeSegment = segB->nextFreeSegment;

                segB->nextSegment->prevSegment = segA;
                segB->nextSegment->prevFreeSegment = segA;
                segB->nextFreeSegment->prevFreeSegment = segA;
            }
            else {
                segB->length += segA->length + sizeof(MemorySegment);
                segB->nextSegment = segA->nextSegment;
                segB->nextFreeSegment = segA->nextFreeSegment;

                segA->nextSegment->prevSegment = segB;
                segA->nextSegment->prevFreeSegment = segB;
                segA->nextFreeSegment->prevFreeSegment = segB;
            }
        }

        /**
         * 1er segment
         */
        MemorySegment* _firstFreeSegment;
    }

    /**
     * Initialise la RAM en allouant un segment XXL qui sera ensuite découpé plus tard
     *
     * @param heapAddress Adresse du segment
     * @param heapLength Taille du segment
     */
    void initHeap(u64 heapAddress, u64 heapLength) {
        _firstFreeSegment = (MemorySegment*) heapAddress;
        _firstFreeSegment->length = heapLength - sizeof(MemorySegment);
        _firstFreeSegment->nextSegment = nullptr;
        _firstFreeSegment->prevSegment = nullptr;
        _firstFreeSegment->nextFreeSegment = nullptr;
        _firstFreeSegment->prevFreeSegment = nullptr;
        _firstFreeSegment->isFree = true;
    }

    /**
     * Alloue de la mémoire.
     * On est honnêtement pas sur la meilleure implémentation qui existe,
     * y a beaucoup de données inutiles pour des petites allocations à cause des infos sur les MemorySegment qu'on
     * doit bien stocker quelque part, mais ça fait le taf c'est ce qui compte.
     *
     * @param size Taille
     *
     * @return Pointeur
     */
    void* malloc(u64 size) {
        // Alignement de la RAM, utile pour meilleures performances sur hardware 64 bits

        u64 remainder = size % 8;
        size -= remainder;

        if (remainder != 0) {
            size += 8;
        }

        std::memory::MemorySegment* currentMemorySegment = std::memory::_firstFreeSegment;

        while (true) {
            if (currentMemorySegment->length >= size) {
                // On a trouvé un segment libre

                if (currentMemorySegment->length != size) {
                    // On va split le segment pour n'allouer que ce qu'il faut

                    MemorySegment* newSegment = (MemorySegment*) ((u64) currentMemorySegment + sizeof(MemorySegment) + size);
                    newSegment->isFree = true;
                    newSegment->length = (u64) currentMemorySegment->length - (sizeof(MemorySegment) + size);
                    newSegment->nextSegment = currentMemorySegment->nextSegment;
                    newSegment->nextFreeSegment = currentMemorySegment->nextFreeSegment;
                    newSegment->prevSegment = currentMemorySegment;
                    newSegment->prevFreeSegment = currentMemorySegment->prevFreeSegment;

                    currentMemorySegment->nextFreeSegment = newSegment;
                    currentMemorySegment->nextSegment = newSegment;
                }

                if (currentMemorySegment == _firstFreeSegment) {
                    // Cas spécial quand 1er segment
                    _firstFreeSegment = currentMemorySegment->nextFreeSegment;
                }

                currentMemorySegment->isFree = false;
                currentMemorySegment->length = size;

                if (currentMemorySegment->prevFreeSegment != nullptr) {
                    // Changement des segments libres de la liste chainée
                    currentMemorySegment->prevFreeSegment->nextFreeSegment = currentMemorySegment->nextFreeSegment;
                }

                if (currentMemorySegment->nextFreeSegment != nullptr) {
                    // Changement des segments libres de la liste chainée
                    currentMemorySegment->nextFreeSegment->prevFreeSegment = currentMemorySegment->prevFreeSegment;
                }

                if (currentMemorySegment->prevSegment != nullptr) {
                    currentMemorySegment->prevSegment->nextFreeSegment = currentMemorySegment->nextFreeSegment;
                }

                if (currentMemorySegment->nextSegment != nullptr) {
                    currentMemorySegment->nextSegment->prevFreeSegment = currentMemorySegment->prevFreeSegment;
                }

                return currentMemorySegment + 1;
            }

            if (currentMemorySegment->nextFreeSegment == nullptr) {
                // Plus de mémoire restante. Normalement impossible, si on arrive ici on doit refaire du paging
                return nullptr;
            }

            currentMemorySegment = currentMemorySegment->nextFreeSegment;
        }
    }

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
    T* memset(_Out_ void* ptr, T value, u64 nb) {
        for (u64 i=0; i<nb; i++) {
            ((T*) ptr)[i] = value;
        }
        return (T*) ptr;
    }

    /**
     * Set un tableau et le modifie
     *
     * @param ptr Pointeur
     * @param value Valeur
     * @param nb Nombre de cases à set
     *
     * @return Tableau
     */
    void* memset(_Out_ void* ptr, int value, u64 nb) {
        return memset<byte>(ptr, value, nb);
    }

    /**
     * Mémoire initialisée à 0
     *
     * @param nb Nombre d'objets
     * @param size Taille d'un objet
     *
     * @return Pointeur
     */
    void* calloc(size_t nb, size_t size) {
        return memset(malloc(nb*size), 0, nb);
    }

    /**
     * Tableau initialisé à 0
     *
     * @tparam T Type
     * @param nb Nombre de cases
     *
     * @return Pointeur
     */
    template<typename T>
    T* calloc(size_t nb) {
        return memset<T>(malloc(nb*sizeof(T)), 0, nb);
    }

    /**
     * Libère de la mémoire
     *
     * @param ptr Pointeur
     */
    void free(_Out_ void* ptr) {
        MemorySegment* currentMemorySegment = ((MemorySegment*) ptr) - 1;
        currentMemorySegment->isFree = true;

        if (currentMemorySegment < _firstFreeSegment) {
            _firstFreeSegment = currentMemorySegment;
        }

        if (currentMemorySegment->nextFreeSegment != nullptr) {
            if (currentMemorySegment->nextFreeSegment->prevFreeSegment < currentMemorySegment) {
                currentMemorySegment->nextFreeSegment->prevFreeSegment = currentMemorySegment;
            }
        }

        if (currentMemorySegment->prevFreeSegment != nullptr) {
            if (currentMemorySegment->prevFreeSegment->nextFreeSegment > currentMemorySegment)
                currentMemorySegment->prevFreeSegment->nextFreeSegment = currentMemorySegment;
        }

        if (currentMemorySegment->nextSegment != nullptr) {
            currentMemorySegment->nextSegment->prevSegment = currentMemorySegment;

            if (currentMemorySegment->nextSegment->isFree) {
                // Évite la fragmentation
                combineFreeSegments(currentMemorySegment, currentMemorySegment->nextSegment);
            }
        }

        if (currentMemorySegment->prevSegment != nullptr) {
            currentMemorySegment->prevSegment->nextSegment = currentMemorySegment;
            if (currentMemorySegment->prevSegment->isFree) {
                // Évite la fragmentation
                combineFreeSegments(currentMemorySegment, currentMemorySegment->prevSegment);
            }
        }
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
