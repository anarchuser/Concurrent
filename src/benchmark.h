#ifndef CONCURRENT_BENCHMARK_H
#define CONCURRENT_BENCHMARK_H

#include "config.h"

#include "functions.h"
#include "time.h"

#include <chrono>
#include <iostream>

void benchmark () {
    auto total = TIME (
        std::cout << "fibonacci\t" << TIME (fibonacci (50)).count() << std::endl;
    );
    std::cout << "total\t" << total.count() << std::endl;
}

#endif //CONCURRENT_BENCHMARK_H

/* Copyright (C) 2020 Aaron Alef */
