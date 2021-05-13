// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 18/09/2020.

#include <cstdint>
#include "memory.h"

namespace stdlib {
    namespace {
        /**
         * Merge two free segments and avoids segmentation
         * @param segA Segment A
         * @param segB Segment B
         */
        void combineFreeSegments(_Inout_ MemorySegmentHeader* segA, _Inout_ MemorySegmentHeader* segB) {
            if (segA == nullptr) {
                return;
            }

            if (segB == nullptr) {
                return;
            }

            if (segA < segB) {
                segA->length += segB->length + sizeof(MemorySegmentHeader);
                segA->nextSegment = segB->nextSegment;
                segA->nextFreeSegment = segB->nextFreeSegment;

                segB->nextSegment->prevSegment = segA;
                segB->nextSegment->prevFreeSegment = segA;
                segB->nextFreeSegment->prevFreeSegment = segA;
            } else {
                segB->length += segA->length + sizeof(MemorySegmentHeader);
                segB->nextSegment = segA->nextSegment;
                segB->nextFreeSegment = segA->nextFreeSegment;

                segA->nextSegment->prevSegment = segB;
                segA->nextSegment->prevFreeSegment = segB;
                segA->nextFreeSegment->prevFreeSegment = segB;
            }
        }

        /**
         * 1st segment
         */
        MemorySegmentHeader* _firstFreeSegment;
    }

    void initHeap(u64 heapAddress, u64 heapLength) {
        _firstFreeSegment = (MemorySegmentHeader*) heapAddress;
        _firstFreeSegment->length = heapLength - sizeof(MemorySegmentHeader);
        _firstFreeSegment->nextSegment = nullptr;
        _firstFreeSegment->prevSegment = nullptr;
        _firstFreeSegment->nextFreeSegment = nullptr;
        _firstFreeSegment->prevFreeSegment = nullptr;
        _firstFreeSegment->isFree = true;
    }

    void* malloc(size_t size) {
        // RAM alignment, useful for better performances on 64 bits hardware

        u64 remainder = size % 8;
        size -= remainder;

        if (remainder != 0) {
            size += 8;
        }

        MemorySegmentHeader* currentMemorySegment = _firstFreeSegment;

        while (true) {
            if (currentMemorySegment->length >= size) {
                // Free segment found

                if (currentMemorySegment->length > size + sizeof(MemorySegmentHeader)) {
                    // Split the segment to allocate only what is needed

                    auto* newSegment = (MemorySegmentHeader*) ((u64) currentMemorySegment + sizeof(MemorySegmentHeader) + size);
                    newSegment->isFree = true;
                    newSegment->length = (u64) currentMemorySegment->length - (sizeof(MemorySegmentHeader) + size);
                    newSegment->nextSegment = currentMemorySegment->nextSegment;
                    newSegment->nextFreeSegment = currentMemorySegment->nextFreeSegment;
                    newSegment->prevSegment = currentMemorySegment;
                    newSegment->prevFreeSegment = currentMemorySegment->prevFreeSegment;

                    currentMemorySegment->nextFreeSegment = newSegment;
                    currentMemorySegment->nextSegment = newSegment;
                    currentMemorySegment->length = size;
                }

                // Special case when 1st segment
                if (currentMemorySegment == _firstFreeSegment) {
                    _firstFreeSegment = currentMemorySegment->nextFreeSegment;
                }

                currentMemorySegment->isFree = false;

                // Change free segments inside the linked list

                if (currentMemorySegment->prevFreeSegment != nullptr) {
                    currentMemorySegment->prevFreeSegment->nextFreeSegment = currentMemorySegment->nextFreeSegment;
                }

                if (currentMemorySegment->nextFreeSegment != nullptr) {
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

            // No more available memory. Shouldn't happen, but if it happens we should do additional paging
            if (currentMemorySegment->nextFreeSegment == nullptr) {
                return nullptr;
            }

            currentMemorySegment = currentMemorySegment->nextFreeSegment;
        }
    }

    void* memset(_Out_ void* ptr, int value, size_t nb) {
        return memset<byte>(ptr, value, nb);
    }

    [[maybe_unused]] void* calloc(size_t nb, size_t size) {
        return memset(malloc(nb*size), 0, nb);
    }

    void free(_Out_ void* ptr) {
        MemorySegmentHeader* currentMemorySegment = ((MemorySegmentHeader*) ptr) - 1;
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
            if (currentMemorySegment->prevFreeSegment->nextFreeSegment > currentMemorySegment) {
                currentMemorySegment->prevFreeSegment->nextFreeSegment = currentMemorySegment;
            }
        }

        if (currentMemorySegment->nextSegment != nullptr) {
            currentMemorySegment->nextSegment->prevSegment = currentMemorySegment;
            if (currentMemorySegment->nextSegment->isFree) {
                // Avoids fragmentation
                combineFreeSegments(currentMemorySegment, currentMemorySegment->nextSegment);
            }
        }

        if (currentMemorySegment->prevSegment != nullptr) {
            currentMemorySegment->prevSegment->nextSegment = currentMemorySegment;
            if (currentMemorySegment->prevSegment->isFree) {
                // Avoids fragmentation
                combineFreeSegments(currentMemorySegment, currentMemorySegment->prevSegment);
            }
        }
    }

    void* realloc(_Inout_ void* ptr, size_t size) {
        void* newPtr = malloc(size);
        memcpy<byte>(newPtr, ptr, size);
        free(ptr);
        return newPtr;
    }

    void* memcpy(_Out_ void* dest, _In_ const void* src, size_t length) {
        return memcpy<byte>(dest, src, length);
    }
}

void* operator new(size_t size) {
    return stdlib::malloc(size);
}

void* operator new[](size_t size) {
    return stdlib::malloc(size);
}

void operator delete(void* p) noexcept {
    stdlib::free(p);
}

void operator delete(void* p, size_t size __attribute__((unused))) noexcept {
    stdlib::free(p);
}

void operator delete[](void* p) noexcept {
    stdlib::free(p);
}

void operator delete[](void* p, size_t size __attribute__((unused))) noexcept {
    stdlib::free(p);
}
