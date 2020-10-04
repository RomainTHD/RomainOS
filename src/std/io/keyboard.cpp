// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 15/09/2020.

#include <io/keyboard.hpp>

namespace std::io {
    /**
     * Namespace anonyme pour garder certaines variables publiques au fichier, privées au projet
     */
    namespace {
        /**
         * Layout actuel
         */
        KeyboardLayout _keyboardLayout;

        /**
         * Type de layout
         */
        KeyboardLayoutType _keyboardLayoutType;

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
    void setKeyboardLayout(KeyboardLayoutType layout) {
        _keyboardLayout = layouts[layout];
        _keyboardLayoutType = layout;
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

        switch (_keyboardLayoutType) {
            case AZERTY:
            default:
                event.key = _keyboardLayout.layout[keyCode];
                break;
        }

        if (event.keyCode == _keyboardLayout.VK_SHIFT) {
            _isShift = !_isShift;
        }
        else if (event.keyCode == _keyboardLayout.VK_ALT) {
            _isAlt = !_isAlt;
        }
        else if (event.keyCode == _keyboardLayout.VK_CAPS_LOCK) {
            if (event.pressed) {
                _isCapsLock = !_isCapsLock;
            }
        }
        else if (event.keyCode == _keyboardLayout.VK_CTRL) {
            _isCtrl = !_isCtrl;
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

        std::io::printChar(event.key);

        if (event.keyCode == _keyboardLayout.VK_ESC) {
            std::system::shutdownAndPrint();
        }
    }
}
