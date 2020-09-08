// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 08/09/2020.

extern "C" void _start() {
    int* ptr = (int*) 0xb8000;
    *ptr = 0x50505050;

    return;
}
