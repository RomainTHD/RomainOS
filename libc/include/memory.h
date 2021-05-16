// SPDX-License-Identifier: GPL-3.0-or-later
/**
 * Memory
 */
// Created by Romain on 18/09/2020.

#ifndef ROMAINOS_MEMORY_H
#define ROMAINOS_MEMORY_H

#include <cstdint>
#include <SAL.h>

namespace stdlib {
    /**
     * RAM segment (linked list)
     */
    struct MemorySegmentHeader {
        /**
         * Length
         */
        u64 length;

        /**
         * Next segment
         */
        MemorySegmentHeader* nextSegment;

        /**
         * Previous segment
         */
        MemorySegmentHeader* prevSegment;

        /**
         * Next free segment
         */
        MemorySegmentHeader* nextFreeSegment;

        /**
         * Previous free segment
         */
        MemorySegmentHeader* prevFreeSegment;

        /**
         * Free segment or not
         */
        bool isFree;
    };

    /**
     * Initialize the RAM by allocating a big chunk of RAM which will later be split in smaller chunks
     * @param heapAddress Segment address
     * @param heapLength Segment size
     */
    void initHeap(u64 heapAddress, u64 heapLength);

    /**
     * Allocate memory. Not the best implementation, it has a lot of overhead because of the MemorySegmentHeader,
     * especially for small allocations, but it works.
     * @param size Allocation size
     * @return Memory pointer
     */
    _Nullable void* malloc(size_t size);

    /**
     * Sets an array and modify it
     * @tparam T Cell type
     * @param ptr Array pointer
     * @param value Value
     * @param nb Number of cells to set
     * @return Array
     */
    template<typename T>
    T* memset(_Out_ void* ptr, T value, size_t nb);

    /**
     * Sets an array and modify it, byte by byte
     * @param ptr Array pointer
     * @param value Value
     * @param nb Number of cells to set
     * @return Array
     */
    void* memset(_Out_ void* ptr, int value, size_t nb);

    /**
     * Like `malloc` but initialize to zero.
     * @param nb Number of objects
     * @param size Object size
     * @return Memory pointer
     */
    void* calloc(size_t nb, size_t size = sizeof(byte));

    /**
     * Like `malloc` but initialize to zero. Used to allocate an array of `T`.
     * @tparam T Cell type
     * @param nb Number of cells
     * @return Memory pointer
     */
    template<typename T>
    T* calloc(size_t nb);

    /**
     * Frees memory
     * @param ptr Pointer
     */
    void free(_Out_ void* ptr);

    /**
     * Reallocate memory
     * @param ptr Pointer
     * @param size New size
     * @return New pointer
     */
    void* realloc(_Inout_ void* ptr, size_t size);

    /**
     * Makes a copy of an array of bytes
     * @param dest Destination
     * @param src Source
     * @param length Number of bytes
     */
    void* memcpy(_Out_ void* dest, _In_ const void* src, size_t length);

    /**
     * Makes a copy of an array of cells`
     * @tparam T Cell type
     * @param dest Destination
     * @param src Source
     * @param length Number of cells
     */
    template <typename T>
    void* memcpy(_Out_ void* dest, _In_ const void* src, size_t length);
}

/**
 * Malloc
 * @see stdlib::malloc
 */
constexpr auto malloc = stdlib::malloc;

/**
 * Free
 * @see stdlib::free
 */
constexpr auto free = stdlib::free;

/**
 * `new` operator
 * @param size Size
 * @return Object pointer
 */
void* operator new(size_t size);

/**
 * `new[]` operator
 * @param size Size
 * @return Array pointer

 */
void* operator new[](size_t size);

/**
 * `delete` operator
 * @param p Pointer
 */
void operator delete(void* p) noexcept;

/**
 * `delete` operator
 * @param p Pointer
 * @param size Size
 */
void operator delete(void* p, size_t size __attribute__((unused))) noexcept;

/**
 * `delete[]` operator
 * @param p Pointer
 */
void operator delete[](void* p) noexcept;

/**
 * `delete[]` operator
 * @param p Pointer
 * @param size Size
 */
void operator delete[](void* p, size_t size __attribute__((unused))) noexcept;

#include "../stdlib/memory.tpp"

#endif //ROMAINOS_MEMORY_H
