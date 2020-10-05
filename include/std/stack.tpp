// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 05/10/2020.

#ifndef ROMAINOS_STACK_TPP
#define ROMAINOS_STACK_TPP

template<typename T>
Stack<T>::Stack() : _first(nullptr), _length(0) {}

template<typename T>
Stack<T>::~Stack() = default;

template<typename T>
void Stack<T>::push(T elem) {
    StackElem* newStack = new StackElem(elem);

    if (!empty()) {
        newStack->next = _first;
    }

    _first = newStack;
    _length++;
}

template<typename T>
T Stack<T>::pop() {
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

template<typename T>
T Stack<T>::peek() const {
    T res;

    if (empty()) {
        // Erreur
    }
    else {
        res = _first->value;
    }

    return res;
}

template<typename T>
size_t Stack<T>::length() const {
    return _length;
}

template<typename T>
bool Stack<T>::empty() const {
    return length() == 0;
}

template<typename T>
Stack<T>::StackElem::StackElem(T elem) : value(elem), next(nullptr) {}

template<typename T>
Stack<T>::StackElem::~StackElem() = default;

#endif //ROMAINOS_STACK_TPP
