// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 15/09/2020.

#ifndef ROMAINOS_KEYBOARD_HPP
#define ROMAINOS_KEYBOARD_HPP

/**
 * Touche non supportée
 */
#define KEY_NOT_SUPPORTED 0xfe

/**
 * Différents layouts
 */
enum KeyboardLayout {
    AZERTY
};

struct KeyEvent {
    char key;
    bool pressed;
    bool ctrl;
    bool alt;
    bool shift;
};

/**
 * Layout actuel
 */
KeyboardLayout _keyboardLayout;

bool _isCtrl;
bool _isAlt;
bool _isShift;

void handleAzerty(byte b, char* out, bool* pressed) {
    // TODO:  Utiliser un tableau pour map ?

    *pressed = !(b & (byte) 0x80);

    if (b >= 0x10 && b <= 0x19) {
        char str[] = "azertyuiop";
        *out = str[b - 0x10];
    }
    else if (b >= 0x1e && b <= 0x27) {
        char str[] = "qsdfghjklm";
        *out = str[b - 0x1e];
    }
    else if (b >= 0x2c && b <= 0x31) {
        char str[] = "wxcvbn";
        *out = str[b - 0x2c];
    }
    else {
        switch (b) {
            case 0x39:
                *out = ' ';
                break;

            case 0x1c:
                *out = '\n';
                break;

            case 0x0f:
                *out = '\t';
                break;

            default:
                *out = (char) KEY_NOT_SUPPORTED;
        }
    }
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
        _isCtrl = false;
        _isAlt = false;
        _isShift = false;
    }

    /**
     * Keyboard to char
     *
     * @param b Byte keyboard
     *
     * @return Char associé
     */
    static KeyEvent getEvent(byte b) {
        KeyEvent event {};

        event.ctrl = _isCtrl;
        event.alt = _isAlt;
        event.shift = _isShift;

        // if (b == 0x)

        switch (_keyboardLayout) {
            case AZERTY:
            default:
                handleAzerty(b, &(event.key), &(event.pressed));
                break;
        }

        return event;
    }
};

/*
void Keyboard::setKeyboardLayout(KeyboardLayout layout) {
    _keyboardLayout = layout;
}*/

#endif //ROMAINOS_KEYBOARD_HPP
