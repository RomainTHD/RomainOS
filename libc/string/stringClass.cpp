// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 10/09/2020.

#include "stringClass.hpp"
#include "stringC.hpp"

string::string(const char* s) {
    this->_s = s;
    this->_length = stdstring::strlen(s);
}

u32 string::length() const {
    return this->_length;
}

const char* string::toChar() const {
    return this->_s;
}
