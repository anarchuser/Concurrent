#ifndef CONCURRENT_BENCHMARK_H
#define CONCURRENT_BENCHMARK_H

#include "../config.h"

#include "../lib/helper.h"
#include "../lib/Executor/Executor.h"
#include "../lib/Task/TimedTask.h"

#include "functions.h"
#include "time.h"

#include <chrono>
#include <iostream>

void benchmark () {
    Executor <TimedTask> executor (MAX_ITEMS);

    auto total = TIME (
            /* Fibonacci */
            auto fib = TIME (for (int x = MAX_FIB - ITERATIONS + 1; x <= MAX_FIB; ++x)
                        executor.schedule (std::make_unique <TimedTask> ([x] { fibonacci (x); })););
            LOG (INFO) << "fibonacci\tΣ\t" << fib;

            /* Sleep / Counter */
            auto sleep = TIME (for (int x = 0; x < ITERATIONS; x++)
                        executor.schedule (std::make_unique <TimedTask> ([] { count_to (SLEEP_IN_MS); })););
            LOG (INFO) << "sleep\tΣ\t" << sleep;
    );
    executor.flush();
    std::cout << "total\tΣ\t" << total << std::endl;
}

#endif //CONCURRENT_BENCHMARK_H

/* Copyright (C) 2020 Aaron Alef */
