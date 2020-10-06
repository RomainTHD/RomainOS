// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 14/09/2020.

#ifndef ROMAINOS_TEXTCOLORMODES_HPP
#define ROMAINOS_TEXTCOLORMODES_HPP

namespace std::io {
    enum {
        FG_BLACK = 0x00,
        FG_BLUE = 0x01,
        FG_GREEN = 0x02,
        FG_CYAN = 0x03,
        FG_RED = 0x04,
        FG_MAGENTA = 0x05,
        FG_BROWN = 0x06,
        FG_LIGHTGRAY = 0x07,
        FG_DARKGRAY = 0x08,
        FG_LIGHTBLUE = 0x09,
        FG_LIGHTGREEN = 0x0a,
        FG_LIGHTCYAN = 0x0b,
        FG_LIGHTRED = 0x0c,
        FG_LIGHTMAGENTA = 0x0d,
        FG_YELLOW = 0x0e,
        FG_WHITE = 0x0f,

        BG_BLACK = 0x00,
        BG_BLUE = 0x10,
        BG_GREEN = 0x20,
        BG_CYAN = 0x30,
        BG_RED = 0x40,
        BG_MAGENTA = 0x50,
        BG_BROWN = 0x60,
        BG_LIGHTGRAY = 0x70,

        BG_BLINKINGBLACK = 0x80,
        BG_BLINKINGBLUE = 0x90,
        BG_BLINKINGGREEN = 0xa0,
        BG_BLINKINGCYAN = 0xb0,
        BG_BLINKINGRED = 0xc0,
        BG_BLINKINGMAGENTA = 0xd0,
        BG_BLINKINGYELLOW = 0xe0,
        BG_BLINKINGWHITE = 0xf0,

        FG_DEFAULT = FG_WHITE,
        BG_DEFAULT = BG_BLUE
    };
}

#endif //ROMAINOS_TEXTCOLORMODES_HPP
