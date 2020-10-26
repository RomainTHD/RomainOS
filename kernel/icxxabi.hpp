// SPDX-License-Identifier: GPL-3.0-or-later
/**
 * Application binary interface
 * Fonctions définies par GCC pour certains cas bien précis
 */
// Created by Romain on 06/10/2020.

#ifndef ROMAINOS_ICXXABI_HPP
#define ROMAINOS_ICXXABI_HPP

/**
 * Nombre max de fonctions at exit
 */
#define ATEXIT_MAX_FUNCS 128

extern "C" {
    typedef unsigned uarch_t;

    /**
     * Entrée de __cxa_atexit
     */
    struct atexit_func_entry_t {
        /**
         * Destructeur
         */
        void (*destructor_func)(void*);

        /**
         * Objet
         */
        void* obj_ptr;

        /**
         * Handle Dynamic Shared Object
         */
        void* dso_handle;
    };

    /**
     * Ajoute un destructeur
     */
    int __cxa_atexit(void (*f)(void*), void* objptr, void* dso);

    /**
     * Appelle un destructeur
     *
     * @param f Destructeur, les appelle tous si NULL
     */
    void __cxa_finalize(void* f);
}

#endif //ROMAINOS_ICXXABI_HPP
