// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 15/09/2020.

#ifndef ROMAINOS_KEYBOARD_HPP
#define ROMAINOS_KEYBOARD_HPP

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

    namespace {
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
            // TODO
            std::IO::setCursorPosition(-1, 0);
            std::IO::printString("Fin du programme...");

            for (int i=0; i<10000000; i++) {}

            std::IO::outw(0x604, 0x2000); // Qemu
            std::IO::outw(0x4004, 0x3400); // VBox
            std::IO::outw(0xB004, 0x2000); // Boshs

            std::IO::setCursorPosition(-1, 0);
            std::IO::printString("Erreur lors de la sortie de l'emulateur !");
            for (int i=0; i<10000000; i++) {}

        }
    }
}

#endif //ROMAINOS_KEYBOARD_HPP
