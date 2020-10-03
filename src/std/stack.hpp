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
    Stack() : _first(nullptr), _length(0) {}

    /**
     * Destructeur
     */
    ~Stack() = default;

    /**
     * Ajoute un élément
     *
     * @param elem Élément
     */
    void push(T elem) {
        StackElem* newStack = new StackElem(elem);

        if (!empty()) {
            newStack->next = _first;
        }

        _first = newStack;
        _length++;
    }

    /**
     * Retire un élément
     *
     * @return Élément
     */
    T pop() {
        T res;

        if (empty()) {
            // Erreur
        }
        else {
            res = _first->value;
            StackElem* oldFirst = _first;
            _first = _first->next;
            delete oldFirst;
            _length--;
        }

        return res;
    }

    /**
     * Sommet de stack
     *
     * @return Sommet
     */
    [[nodiscard]] T peek() const {
        T res;

        if (empty()) {
            // Erreur
        }
        else {
            res = _first->value;
        }
    }

    /**
     * Taille de la pile
     *
     * @return Taille
     */
    [[nodiscard]] size_t length() const {
        return _length;
    }

    /**
     * Vide ou non
     *
     * @return Vide ?
     */
    [[nodiscard]] bool empty() const {
        return length() == 0;
    }

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
        explicit StackElem(T elem) : value(elem), next(nullptr) {}

        /**
         * Destructeur
         */
        ~StackElem() = default;

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

#endif //ROMAINOS_STACK_HPP
