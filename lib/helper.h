#ifndef CONCURRENT_HELPER_H
#define CONCURRENT_HELPER_H

#include <chrono>
#include <iomanip>
#include <iostream>
#include <ostream>

template <typename T>
concept Streamable = requires (std::ostream & os, T const & t) { os << t; };

template <typename T>
concept Runnable = requires (T & t) { t (); };

void test();

template <typename T, typename R>
std::ostream & operator << (std::ostream & os, std::chrono::duration <T, R> duration) {
    return os << std::chrono::duration_cast <std::chrono::microseconds> (duration).count() << " μs";
}
std::ostream & operator << (std::ostream & os, std::chrono::time_point <std::chrono::high_resolution_clock> const & time);

#endif //CONCURRENT_HELPER_H

/* Copyright (C) 2020 Aaron Alef */
