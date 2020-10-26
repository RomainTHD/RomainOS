// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 15/09/2020.

#ifndef ROMAINOS_KEYBOARD_HPP
#define ROMAINOS_KEYBOARD_HPP

#include <cstdint>
#include <stack>

#include "keyboardLayout.hpp"

namespace stdio::keyboard {
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
     * Gère un évènement
     *
     * @param b Code
     */
    void _notifyEvent(byte b);

    /**
     * Ajoute une fonction en handler
     *
     * @param f Fonction
     */
    void addEventHandler(void (*f)(KeyEvent));

    /**
     * Supprime une fonction en handler
     *
     * @param f Fonction
     */
    void deleteEventHandler(void (*f)(KeyEvent));

    /**
     * Set la disposition clavier
     *
     * @param layout Layout
     */
    void setKeyboardLayout(KeyboardLayoutType layout);
}

#endif //ROMAINOS_KEYBOARD_HPP
