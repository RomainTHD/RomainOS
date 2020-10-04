// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 15/09/2020.

#ifndef ROMAINOS_KEYBOARD_HPP
#define ROMAINOS_KEYBOARD_HPP

#include <system.hpp>

#include "keyboardLayout.hpp"

namespace std::io {
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
     * Set la disposition clavier
     *
     * @param layout Layout
     */
    void setKeyboardLayout(KeyboardLayoutType layout);

    /**
     * Keyboard to char
     *
     * @param b Byte keyboard
     *
     * @return Char associé
     */
    KeyEvent getEvent(byte keyCode);

    /**
     * Gère un évènement
     *
     * @param b Code
     */
    void handleEvent(byte b);
}

#endif //ROMAINOS_KEYBOARD_HPP
