// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 18/09/2020.

#ifndef ROMAINOS_AZERTY_HPP
#define ROMAINOS_AZERTY_HPP

#define VK_ESC 0x01
#define VK_DEL 0x0e
#define VK_SHIFT 0x2a
#define VK_ALT 0x38
#define VK_CTRL 0x1d
#define VK_CAPS_LOCK 0x3a

namespace std::io {
    static char _layoutAZERTY[256] = {
            //        0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
            /* 0 */ '\0', 0x1b, '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , '0' , ')' , '=' , 0x7f, '\t',
            /* 1 */ 'a' , 'z' , 'e' , 'r' , 't' , 'y' , 'u' , 'i' , 'o' , 'p' , '^' , '$' , '\n', '\0', 'q' , 's' ,
            /* 2 */ 'd' , 'f' , 'g' , 'h' , 'j' , 'k' , 'l' , 'm' , '%' , '2' , '\0', '*' , 'w' , 'x' , 'c' , 'v' ,
            /* 3 */ 'b' , 'n' , ',' , ';' , ':' , '!' , '\0', '*' , '\0', ' ' , '\0', '\0', '\0', '\0', '\0', '\0',
            /* 3 */ '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    };
}

/*
 * 00:
 * 01: ESC
 * 0e: DEL
 * 1d:
 * 28: ù
 * 29: ²
 * 2a: SHIFT
 * 36: WIN ?
 * 38: ALT
 * 3a: Caps Lock
 * 3b à 44: F1 à F10
 * 45: Pause
 * 46: Arrêt défil
 */

#endif //ROMAINOS_AZERTY_HPP
