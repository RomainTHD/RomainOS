// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 06/10/2020.

#include "icxxabi.hpp"

extern "C" {
    atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];

    unsigned __atexit_func_count = 0;

    // TODO: Remove this `= 0` and put it inside the assembly ?
    // FIXME: Use NULL instead
    void* __dso_handle = 0;

    int __cxa_atexit(void (*f)(void*), void* objptr, void* dso) {
        if (__atexit_func_count >= ATEXIT_MAX_FUNCS) {
            // Too many destructors
            // FIXME: Perhaps do something here ?
            return -1;
        }

        __atexit_funcs[__atexit_func_count].destructor_func = f;
        __atexit_funcs[__atexit_func_count].obj_ptr = objptr;
        __atexit_funcs[__atexit_func_count].dso_handle = dso;
        __atexit_func_count++;

        return 0;
    }

    void __cxa_finalize(void* f) {
        unsigned i = __atexit_func_count;

        if (!f) {
            /*
             * According to the Itanium C++ ABI documentation, if __cxa_finalize is called without function pointer
             * everything must be removed
             * TODO: monitor the links still belonging to the DSO ?
             */

            while (i != 0) {
                if (__atexit_funcs[i].destructor_func) {
                    /*
                     * Safeguard pour éviter d'appeler un destructeur sur un objet déjà détruit
                     */
                    (*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
                }

                i--;
            }

            return;
        }

        while (i != 0) {
            /*
             * Obviously the destructors should only be called once
             * FIXME: Problem, all the destructors have to be in the right order,
             *        but removing some would introduce holes. Should be modified to move the destructors without holes,
             *        it would be wasted space
             */

            if (__atexit_funcs[i].destructor_func == f) {
                (*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
                __atexit_funcs[i].destructor_func = 0;
                // FIXME: We should decrement `__atexit_func_count` but we would have to fix the previous bug
            }

            i--;
        }
    }
}
