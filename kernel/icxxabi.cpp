// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 06/10/2020.

#include "icxxabi.hpp"

extern "C" {
    atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];

    uarch_t __atexit_func_count = 0;

    // TODO: Supprimer le '= 0' et le mettre dans la partie ASM
    void* __dso_handle = 0;

    int __cxa_atexit(void (*f)(void*), void* objptr, void* dso) {
        if (__atexit_func_count >= ATEXIT_MAX_FUNCS) {
            // Si trop de destructeurs
            return -1;
        }

        __atexit_funcs[__atexit_func_count].destructor_func = f;
        __atexit_funcs[__atexit_func_count].obj_ptr = objptr;
        __atexit_funcs[__atexit_func_count].dso_handle = dso;
        __atexit_func_count++;

        return 0;
    }

    void __cxa_finalize(void* f) {
        uarch_t i = __atexit_func_count;

        if (!f) {
            /*
             * D'après la doc Itanium C++ ABI, si __cxa_finalize est appelée sans pointeur de fonction c'est que
             * tout doit être détruit
             *
             * TODO: monitorer ici les liens encore existant aux DSO ?
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
             * Évidemment les destructeurs doivent pas être appelés plusieurs fois, un seul appel est nécessaire
             *
             * FIXME:
             * Petit soucis, tous les destructeurs doivent être dans l'ordre, mais en retirer un créerait des trous.
             * Doit être modifié pour déplacer les destructeurs et éviter les trous, qui représentent de l'espace gâché
             */

            if (__atexit_funcs[i].destructor_func == f) {
                (*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
                __atexit_funcs[i].destructor_func = 0;

                // On devrait ici décrémenter __atexit_func_count mais pour ça il faudrait fix le bug précédent...
            }

            i--;
        }
    }
}
