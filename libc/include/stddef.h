// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 25/10/2020.

#ifndef ROMAINOS_STDDEF_H
#define ROMAINOS_STDDEF_H

#define NULL ((char*) 0)

namespace stddef {
    /**
     * Si la variable est un pointeur ou non
     *
     * @tparam T Type
     *
     * @return Pointeur ou non
     */
    template<typename T>
    bool isPointer(T);
}

#endif //ROMAINOS_STDDEF_H
