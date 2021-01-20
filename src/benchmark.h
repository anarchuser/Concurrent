#ifndef CONCURRENT_BENCHMARK_H
#define CONCURRENT_BENCHMARK_H

#include "../config.h"

#include "functions.h"
#include "helpers.h"
#include "time.h"

#include <chrono>
#include <iostream>

void benchmark () {
    auto total = TIME (
            /* Fibonacci */
            auto fib = TIME (
                    for (int x = MAX_FIB - ITERATIONS + 1; x <= MAX_FIB; ++x) {
                        std::cout << "fibonacci\t" << x << "\t" << TIME (fibonacci (x)) << std::endl;
                    });
            std::cout << "fibonacci\tΣ\t" << fib << std::endl;

            /* Sleep / Counter */
            auto sleep = TIME (
                    for (int x = 0; x < ITERATIONS; x++)
                        std::cout << "sleep\t" << x << "\t" << TIME (
                                count_to (5000)) << std::endl;);
            std::cout << "sleep\tΣ\t" << sleep << std::endl;
    );
    std::cout << "total\tΣ\t" << total << std::endl;
}

#endif //CONCURRENT_BENCHMARK_H

/* Copyright (C) 2020 Aaron Alef */
