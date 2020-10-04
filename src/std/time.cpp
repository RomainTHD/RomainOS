// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 26/09/2020.

#include <time.hpp>

namespace std::time {
    TimeScale::TimeScale(u64 micro) : _micro(micro) {}
    TimeScale::TimeScale() : TimeScale(0) {}
    TimeScale::~TimeScale() = default;

    TimeScale TimeScale::fromSec(u32 s) {
        return TimeScale(s*10e6);
    }

    TimeScale TimeScale::fromMilli(u32 ms) {
        return TimeScale(ms*10e3);
    }

    TimeScale TimeScale::fromMicro(u64 micro) {
        return TimeScale(micro);
    }

    u64 TimeScale::toMicro() const {
        return _micro;
    }

    u32 TimeScale::toMilli() const {
        return toMicro() / 10e3;
    }

    u32 TimeScale::toSec() const {
        return toMicro() / 10e6;
    }

    TimeScale& TimeScale::setSec(u32 sec) {
        setMicro(sec*10e6);
        return *this;
    }

    TimeScale& TimeScale::setMilli(u32 ms) {
        setMicro(ms*10e3);
        return *this;
    }

    TimeScale& TimeScale::setMicro(u64 micro) {
        this->_micro = micro;
        return *this;
    }

    TimeScale& TimeScale::addSec(u32 sec) {
        setMicro(toMicro() + sec*10e6);
        return *this;
    }

    TimeScale& TimeScale::addMilli(u32 ms) {
        setMicro(toMicro() + ms*10e3);
        return *this;
    }

    TimeScale& TimeScale::addMicro(u64 micro) {
        setMicro(toMicro() + micro);
        return *this;
    }

    void sleep(_In_ const TimeScale& scale) {
        for (u64 i=0; i<scale.toMicro()*4; i++) {
            asm ("nop");
        }
    }

    void sleep(u32 s, u32 micro) {
        sleep(TimeScale::fromSec(s).addMicro(micro));
    }
}
