// SPDX-License-Identifier: GPL-3.0-or-later
/**
 * Standard ints
 */
// Created by Romain on 25/10/2020.

#ifndef ROMAINOS_STDINT_H
#define ROMAINOS_STDINT_H

// FIXME: Remove this include, added for backward compatibility only
#include <SAL.h>

/**
 * Unsigned int 8 bits. 0 to 255
 */
typedef unsigned char      uint8_t;

/**
 * Signed int 8 bits. -128 to 127
 */
typedef signed   char       int8_t;

/**
 * Unsigned int 16 bits. 0 to 65,535
 */
typedef unsigned short     uint16_t;

/**
 * Signed int 16 bits. -32768 to 32,767
 */
typedef signed   short      int16_t;

/**
 * Unsigned int 32 bits. 0 to 4,294,967,295
 */
typedef unsigned long      uint32_t;

/**
 * Signed int 32 bits. -2,147,483,648 to 2,147,483,647
 */
typedef signed   long       int32_t;

/**
 * Unsigned int 64 bits. Approx 1.84 * 10^19
 */
typedef unsigned long long uint64_t;

/**
 * Signed int 64 bits. Approx ± 9.22 * 10^18
 */
typedef signed   long long  int64_t;

/**
 * Unsigned int 8 bits. 0 to 255
 */
typedef uint8_t  u8;

/**
 * Signed int 8 bits. -128 to 127
 */
typedef  int8_t  i8;

/**
 * Unsigned int 16 bits. 0 to 65,535
 */
typedef uint16_t u16;

/**
 * Signed int 16 bits. -32768 to 32,767
 */
typedef  int16_t i16;

/**
 * Unsigned int 32 bits. 0 to 4,294,967,295
 */
typedef uint32_t u32;

/**
 * Signed int 64 bits. Approx ± 9.22 * 10^18
 */
typedef  int32_t i32;

/**
 * Unsigned int 64 bits. Approx 1.84 * 10^19
 */
typedef uint64_t u64;

/**
 * Signed int 64 bits. Approx ± 9.22 * 10^18
 */
typedef  int64_t i64;

/**
 * Unsigned int 8 bits. 0 to 255
 */
typedef uint8_t byte;

/**
 * Size. 32 bits
 */
typedef unsigned long long size_t;

#endif //ROMAINOS_STDINT_H
