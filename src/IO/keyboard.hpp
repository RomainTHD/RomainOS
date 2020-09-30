// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 15/09/2020.

#ifndef ROMAINOS_KEYBOARD_HPP
#define ROMAINOS_KEYBOARD_HPP

#include <system.hpp>

#include "keyboardLayouts/AZERTY.hpp"

namespace std::IO {
    /**
     * Différents layouts
     */
    enum KeyboardLayout {
        AZERTY
    };

    /**
     * Event clavier
     */
    struct KeyEvent {
        /**
         * Caractère ('a', '1'...), '\0' si caractère spécial
         */
        char key;

        /**
         * Code clavier (0x1e pour 'q')
         */
        byte keyCode;

        /**
         * Code clavier raw (0x1e pour 'q' pressé, ox9e pour 'q' relâché)
         */
        byte keyCodeRaw;

        /**
         * Touche enfoncée ou non
         */
        bool pressed;

        /**
         * Est en ctrl ou non
         */
        bool ctrl;

        /**
         * Est en alt ou non
         */
        bool alt;

        /**
         * Est en shift ou non
         */
        bool shift;
    };

    /**
     * Namespace anonyme pour garder certaines variables publiques au fichier, privées au projet
     */
    namespace {
        /**
         * Layout actuel
         */
        KeyboardLayout _keyboardLayout = AZERTY;

        /**
         * Est en ctrl ou non
         */
        bool _isCtrl = false;

        /**
         * Est en alt ou non
         */
        bool _isAlt = false;

        /**
         * Est en shift ou non
         */
        bool _isShift = false;

        /**
         * Est en caps lock ou non
         */
        bool _isCapsLock = false;
    }

    /**
     * Set la disposition clavier
     *
     * @param layout Layout
     */
    void setKeyboardLayout(KeyboardLayout layout) {
        _keyboardLayout = layout;
        _isCtrl = false;
        _isAlt = false;
        _isShift = false;
        _isCapsLock = false;
    }

    /**
     * Keyboard to char
     *
     * @param b Byte keyboard
     *
     * @return Char associé
     */
    KeyEvent getEvent(byte keyCode) {
        KeyEvent event {};

        event.key = '\0';
        event.keyCode = (byte) (keyCode << (byte) 1) >> (byte) 1;
        event.keyCodeRaw = keyCode;
        event.pressed = !(keyCode & (byte) 0x80);
        event.ctrl = _isCtrl;
        event.alt = _isAlt;
        event.shift = _isShift;

        switch (_keyboardLayout) {
            case AZERTY:
            default:
                event.key = _layoutAZERTY[keyCode];
                break;
        }

        switch (event.keyCode) {
            case VK_SHIFT:
                _isShift = !_isShift;
                break;

            case VK_ALT:
                _isAlt = !_isAlt;
                break;

            case VK_CAPS_LOCK:
                if (event.pressed) {
                    _isCapsLock = !_isCapsLock;
                }
                break;

            case VK_CTRL:
                _isCtrl = !_isCtrl;
                break;

            default:
                break;
        }

        if (event.shift xor _isCapsLock) {
            if (event.key >= 'a' && event.key <= 'z') {
                event.key += ('A' - 'a');
            }
        }

        return event;
    }

    /**
     * Gère un évènement
     *
     * @param b Code
     */
    void handleEvent(byte b) {
        KeyEvent event = getEvent(b);
        std::IO::printChar(event.key);

        if (event.keyCode == VK_ESC) {
            std::system::shutdownAndPrint();
        }
    }
}

#endif //ROMAINOS_KEYBOARD_HPP
