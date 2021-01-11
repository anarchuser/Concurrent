#ifndef CONCURRENT_BENCHMARK_H
#define CONCURRENT_BENCHMARK_H

#include "config.h"

#include "functions.h"
#include "helpers.h"
#include "time.h"

#include <chrono>
#include <iostream>

void benchmark () {
    auto total = TIME (
            for (int x = 0; x < 50; ++x) {
                std::cout << "fibonacci\t" << TIME (LOG (INFO) << fibonacci (x)) << std::endl;
            }
    );
    std::cout << "total\t" << total.count() << std::endl;
}

#endif //CONCURRENT_BENCHMARK_H

/* Copyright (C) 2020 Aaron Alef */
