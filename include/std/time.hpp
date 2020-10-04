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
        explicit TimeScale(u64 micro);

        /**
         * Constructeur
         */
        TimeScale();

        /**
         * Destructeur
         */
        ~TimeScale();

        /**
         * Constructeur depuis secondes
         *
         * @param s Secondes
         *
         * @return TimeScale
         */
        static TimeScale fromSec(u32 s);

        /**
         * Constructeur depuis millisecondes
         *
         * @param ms Millisecondes
         *
         * @return TimeScale
         */
        static TimeScale fromMilli(u32 ms);

        /**
         * Constructeur depuis microsecondes
         *
         * @param micro Microsecondes
         *
         * @return TimeScale
         */
        static TimeScale fromMicro(u64 micro);

        /**
         * @return To microseconds
         */
        [[nodiscard]] u64 toMicro() const;

        /**
         * @return To milliseconds
         */
        [[nodiscard]] u32 toMilli() const;

        /**
         * @return To seconds
         */
        [[nodiscard]] u32 toSec() const;

        /**
         * Set selon secondes
         *
         * @param sec Secondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& setSec(u32 sec);

        /**
         * Set selon millisecondes
         *
         * @param ms Millisecondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& setMilli(u32 ms);

        /**
         * Set selon microsecondes
         *
         * @param micro Microsecondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& setMicro(u64 micro);

        /**
         * Ajoute des secondes
         *
         * @param sec Secondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& addSec(u32 sec);

        /**
         * Ajoute des millisecondes
         *
         * @param ms Millisecondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& addMilli(u32 ms);

        /**
         * Ajoute des microsecondes
         *
         * @param micro Microsecondes
         *
         * @return TimeScale modifiée
         */
        TimeScale& addMicro(u64 micro);

    private:
        /**
         * Microsecondes
         */
        u64 _micro;
    };

    /**
     * Sleep
     *
     * @param scale Temps
     */
    void sleep(_In_ const TimeScale& scale);

    /**
     * Sleep
     *
     * @param s Secondes
     * @param micro Microsecondes
     */
    void sleep(u32 s, u32 micro = 0);
}

#endif //ROMAINOS_TIME_HPP
