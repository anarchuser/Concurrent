#ifndef CONCURRENT_TIME_H
#define CONCURRENT_TIME_H

#include <chrono>

#define LOG_TIME(expr) {                                            \
    auto __start__ = std::chrono::high_resolution_clock::now();     \
    try { expr; }                                                   \
    catch (std::exception & e) {                                    \
        auto __stop__ = std::chrono::high_resolution_clock::now();  \
        LOG (INFO) << "This expression failed after " <<            \
        std::chrono::duration_cast <std::chrono::microseconds>      \
                (__stop__ - __start__).count() <<                   \
                " microseconds.";                                   \
        throw;                                                      \
    }                                                               \
    auto __stop__ = std::chrono::high_resolution_clock::now();      \
    LOG (INFO) << "This expression took " <<                        \
    std::chrono::duration_cast <std::chrono::microseconds>          \
            (__stop__ - __start__).count() <<                       \
    " microseconds to execute";} true


#define TIME(expr) [] () -> std::chrono::microseconds {             \
    auto __start__ = std::chrono::high_resolution_clock::now();     \
    try { expr; }                                                   \
    catch (std::exception & e) {                                    \
        auto __stop__ = std::chrono::high_resolution_clock::now();  \
        LOG (INFO) << "This expression took " <<                    \
        std::chrono::duration_cast <std::chrono::microseconds>      \
                (__stop__ - __start__).count() <<                   \
                " microseconds to execute";                         \
        throw;                                                      \
    }                                                               \
    auto __stop__ = std::chrono::high_resolution_clock::now();      \
    return std::chrono::duration_cast                               \
            <std::chrono::microseconds> (__stop__ - __start__);}()

#endif //CONCURRENT_TIME_H

/* Copyright (C) 2020 Aaron Alef */
