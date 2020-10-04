// SPDX-License-Identifier: GPL-3.0-or-later
/**
 * Interruptions IDT (Interrupt Descriptor Tables)
 *
 * @see https://wiki.osdev.org/Interrupt_Descriptor_Table
 */
// Created by Romain on 14/09/2020.

#ifndef ROMAINOS_IDT_HPP
#define ROMAINOS_IDT_HPP

#include <types.hpp>

#include "keyboard.hpp"

namespace std::io::idt {
    /**
     * Interrupt Descriptor Tables
     */
    struct IDT64 {
        /**
         * Offset bits 0..15
         */
        uint16_t offsetLow;

        /**
         * Code segment selector, dans GDT ?
         */
        uint16_t selector;

        /**
         * Les bits 0 à 2 contiennent l'offset Interrupt Stack Table, les autres bits sont à 0
         */
        uint8_t ist;

        /**
         * Type et attributs
         */
        uint8_t types_attr;

        /**
         * Offset bits 16..31
         */
        uint16_t offsetMid;

        /**
         * Offset bits 32..63
         */
        uint32_t offsetHigh;

        /**
         * Réservé
         */
        uint32_t zero;
    };

    /**
     * Initialise les interruptions
     */
    void initIDT();
}

#endif //ROMAINOS_IDT_HPP
