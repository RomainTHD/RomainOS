// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 26/09/2020.

#ifndef ROMAINOS_TIME_HPP
#define ROMAINOS_TIME_HPP

#include <types.hpp>

namespace std::time {
    /**
     * Temps
     */
    class TimeScale {
    public:
        /**
         * Constructeur
         *
         * @param micro Microsecondes
         */
        explicit TimeScale(u64 micro) : _micro(micro) {}

        /**
         * Constructeur
         */
        TimeScale() : TimeScale(0) {}

        /**
         * Destructeur
         */
        virtual ~TimeScale() = default;

        /**
         * Constructeur depuis secondes
         *
         * @param s Secondes
         *
         * @return TimeScale
         */
        static TimeScale fromSec(u32 s) {
            return TimeScale(s*10e6);
        }

        /**
         * Constructeur depuis millisecondes
         *
         * @param ms Millisecondes
         *
         * @return TimeScale
         */
        static TimeScale fromMilli(u32 ms) {
            return TimeScale(ms*10e3);
        }

        /**
         * Constructeur depuis microsecondes
         *
         * @param micro Microsecondes
         *
         * @return TimeScale
         */
        static TimeScale fromMicro(u64 micro) {
            return TimeScale(micro);
        }

        /**
         * @return To microseconds
         */
        [[nodiscard]] u64 toMicro() const {
            return _micro;
        }

        /**
         * @return To milliseconds
         */
        [[nodiscard]] u32 toMilli() const {
            return toMicro() / 10e3;
        }

        /**
         * @return To seconds
         */
        [[nodiscard]] u32 toSec() const {
            return toMicro() / 10e6;
        }

        /**
         * Set selon secondes
         *
         * @param sec Secondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& setSec(u32 sec) {
            setMicro(sec*10e6);
            return *this;
        }

        /**
         * Set selon millisecondes
         *
         * @param ms Millisecondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& setMilli(u32 ms) {
            setMicro(ms*10e3);
            return *this;
        }

        /**
         * Set selon microsecondes
         *
         * @param micro Microsecondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& setMicro(u64 micro) {
            this->_micro = micro;
            return *this;
        }

        /**
         * Ajoute des secondes
         *
         * @param sec Secondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& addSec(u32 sec) {
            setMicro(toMicro() + sec*10e6);
            return *this;
        }

        /**
         * Ajoute des millisecondes
         *
         * @param ms Millisecondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& addMilli(u32 ms) {
            setMicro(toMicro() + ms*10e3);
            return *this;
        }

        /**
         * Ajoute des microsecondes
         *
         * @param micro Microsecondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& addMicro(u64 micro) {
            setMicro(micro);
            return *this;
        }
    private:
        /**
         * Microsecondes
         */
        u64 _micro;
    };
}

namespace std::time {
    /**
     * Sleep
     *
     * @param scale Temps
     */
    void sleep(const TimeScale& scale) {
        for (u64 i=0; i<scale.toMicro(); i++) {
            asm ("nop");
        }
    }

    /**
     * Sleep
     *
     * @param s Secondes
     * @param micro Microsecondes
     */
    [[deprecated("Replaced by sleep(const TimeScale&)")]]
    void sleep(u32 s, u32 micro = 0) {
        u64 micro64 = micro + ((u64) s)*10e6;

        for (u64 i=0; i<micro64; i++) {
            asm ("nop");
        }
    }
}

#endif //ROMAINOS_TIME_HPP
