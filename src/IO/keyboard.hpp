// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 15/09/2020.

#ifndef ROMAINOS_KEYBOARD_HPP
#define ROMAINOS_KEYBOARD_HPP

/**
 * Différents layouts
 */
enum KeyboardLayout {
    AZERTY
};

/**
 * Layout actuel
 */
KeyboardLayout _keyboardLayout;

char handleAzerty(byte b) {
    char str[] = "azertyuiop";

    if (b >= 0x10 && b <= 0x19) {
        return str[b - 0x10];
    }

    return 'x';
}

/**
 * Classe clavier
 */
class Keyboard {
public:
    /**
     * Suppression du constructeur
     */
    Keyboard() = delete;

    /**
     * Destructeur
     */
    ~Keyboard() = default;

    /**
     * Set la disposition clavier
     *
     * @param layout Layout
     */
    static void setKeyboardLayout(KeyboardLayout layout) {
        _keyboardLayout = layout;
    }

    /**
     * Keyboard to char
     *
     * @param b Byte keyboard
     *
     * @return Char associé
     */
    static char toChar(byte b) {
        switch (_keyboardLayout) {
            case AZERTY:
                return handleAzerty(b);
                break;

            default:
                return '$';
        }
    }
};

/*
void Keyboard::setKeyboardLayout(KeyboardLayout layout) {
    _keyboardLayout = layout;
}*/

#endif //ROMAINOS_KEYBOARD_HPP
