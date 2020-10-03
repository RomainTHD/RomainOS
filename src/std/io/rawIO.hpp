// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 09/09/2020.

#ifndef ROMAINOS_RAWIO_HPP
#define ROMAINOS_RAWIO_HPP

#include <types.hpp>

namespace std::io {
    /**
     * Transfère de la data à travers les ports sur un octet
     *
     * @param port Port utilisé. Compris entre 0x03b0 et 0x03df pour du VGA
     * @param val Valeur à transférer
     *
     * @see https://wiki.osdev.org/I/O_Ports#The_list
     */
    void outb(u16 port, byte val) {
        // Volatile pour empêcher le compilateur io'optimiser
        asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
    }

    /**
     * Transfère de la data à travers les ports sur deux octets
     *
     * @param port Port utilisé
     * @param val Valeur à transférer
     */
    void outw(u16 port, u16 val) {
        asm volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
    }

    /**
     * Récupère de la data à travers les ports
     *
     * @param port Port utilisé. Compris entre 0x03b0 et 0x03df pour du VGA
     *
     * @return Data
     *
     * @see https://wiki.osdev.org/I/O_Ports#The_list
     */
    byte inb(u16 port) {
        byte res;

        asm volatile ("inb %1, %0"
        : "=a"(res)
        : "Nd"(port)
        );

        return res;
    }
}
#endif //ROMAINOS_RAWIO_HPP