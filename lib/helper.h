#ifndef CONCURRENT_HELPER_H
#define CONCURRENT_HELPER_H

#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>

template <typename T>
concept Streamable = requires (std::ostream & os, T const & t) { os << t; };

template <typename T>
concept Runnable = requires (T & t) { t (); };

template <class B, class D>
concept Subclass = std::is_base_of <D, B>::value;

template <typename T, typename R>
std::ostream & operator << (std::ostream & os, std::chrono::duration <T, R> duration) {
    auto dura = std::to_string (std::chrono::duration_cast <std::chrono::nanoseconds> (duration).count());
    for (std::size_t idx = 0; idx < dura.size(); idx++) {
        os << dura [idx];
        if (idx % 3 == (dura.size() - 1) % 3 && idx != dura.size() - 1)
            os << '\'';
    }
    return os << " ns";
}
std::ostream & operator << (std::ostream & os, std::chrono::time_point <std::chrono::high_resolution_clock> const & time);

#endif //CONCURRENT_HELPER_H

/* Copyright (C) 2020 Aaron Alef */
