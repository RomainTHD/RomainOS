// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 04/10/2020.

#ifndef ROMAINOS_KEYBOARDLAYOUT_HPP
#define ROMAINOS_KEYBOARDLAYOUT_HPP

namespace stdio::keyboard {
    extern char VK_ESC;
    extern char VK_DEL;
    extern char VK_SHIFT;
    extern char VK_ALT;
    extern char VK_CTRL;
    extern char VK_CAPS_LOCK;

    struct KeyboardLayout {
        char layout[256];
        char VK_ESC;
        char VK_DEL;
        char VK_SHIFT;
        char VK_ALT;
        char VK_CTRL;
        char VK_CAPS_LOCK;
    };

    typedef enum {
        AZERTY = 0,
        QWERTY = 1
    } KeyboardLayoutType;

    void setLayoutSpecialChars(KeyboardLayoutType type);

    extern KeyboardLayout layouts[2];
}

#endif //ROMAINOS_KEYBOARDLAYOUT_HPP
