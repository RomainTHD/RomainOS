// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 09/09/2020.

#include <types.hpp>

namespace {
    /**
     * @see isPointer
     */
    template<typename T>
    struct _isPointer {
        static const bool value = false;
    };

    /**
     * @see isPointer
     */
    template<typename T>
    struct _isPointer<T*> {
        static const bool value = true;
    };
}

namespace std::types {
    template<typename T>
    bool isPointer(T) {
        return _isPointer<T>::value;
    }
}
