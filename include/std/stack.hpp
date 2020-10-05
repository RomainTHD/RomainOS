// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 11/09/2020.

#ifndef ROMAINOS_STACK_HPP
#define ROMAINOS_STACK_HPP

#include <types.hpp>

/**
 * Stack
 *
 * @tparam T Type du contenu
 */
template<typename T>
class Stack {
public:
    /**
     * Constructeur
     */
    Stack();

    /**
     * Destructeur
     */
    ~Stack();

    /**
     * Ajoute un élément
     *
     * @param elem Élément
     */
    void push(T elem);

    /**
     * Retire un élément
     *
     * @return Élément
     */
    T pop();

    /**
     * Sommet de stack
     *
     * @return Sommet
     */
    [[nodiscard]] T peek() const;

    /**
     * Taille de la pile
     *
     * @return Taille
     */
    [[nodiscard]] size_t length() const;

    /**
     * Vide ou non
     *
     * @return Vide ?
     */
    [[nodiscard]] bool empty() const;

private:
    /**
     * Élément de la pile
     */
    class StackElem {
    public:
        /**
         * Constructeur
         *
         * @param elem Élément
         */
        explicit StackElem(T elem);

        /**
         * Destructeur
         */
        ~StackElem();

        /**
         * Élément
         */
        T value;

        /**
         * Next
         */
        StackElem* next;
    };

    /**
     * Sommet de pile
     */
    StackElem* _first;

    /**
     * Taille de la pile
     */
    size_t _length;
};

#include "stack.tpp"

#endif //ROMAINOS_STACK_HPP
