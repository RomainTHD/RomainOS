// SPDX-License-Identifier: GPL-3.0-or-later
/**
 * Application Binary Interface
 * Functions defined by GCC, like destructors
 */
// Created by Romain on 06/10/2020.

#ifndef ROMAINOS_ICXXABI_HPP
#define ROMAINOS_ICXXABI_HPP

/**
 * Max number of functions at exit
 */
#define ATEXIT_MAX_FUNCS 128

extern "C" {
    /**
     * Entry point of `__cxa_atexit`
     */
    struct atexit_func_entry_t {
        /**
         * Destructor
         */
        void (*destructor_func)(void*);

        /**
         * Current object
         */
        void* obj_ptr;

        /**
         * Handle Dynamic Shared Object
         */
        void* dso_handle;
    };

    /**
     * Adds a destructor
     * @param f Destructor
     * @param objptr Current object
     * @param dso DSO
     * @return 0 if it went fine, else -1
     */
    int __cxa_atexit(void (*f)(void*), void* objptr, void* dso);

    /**
     * Calls the destructor
     * @param f Destructor, calls them all if NULL
     */
    void __cxa_finalize(void* f);
}

#endif //ROMAINOS_ICXXABI_HPP
