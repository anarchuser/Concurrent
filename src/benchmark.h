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
    auto total = TIME (
            Executor<TimedTask> executor;

            /* Fibonacci */
            for (int x = MAX_FIB - ITERATIONS + 1; x <= MAX_FIB; ++x)
                executor.schedule(std::make_unique<TimedTask>([x] { fibonacci(x); }));

            /* Sleep / Counter */
            for (int x = 0; x < ITERATIONS; x++)
                executor.schedule (std::make_unique <TimedTask> ([] { count_to (SLEEP_IN_MS); }));
    );
    STD_OSTREAM << "threads\t" << AVAILABLE_THREADS << std::endl;
    STD_OSTREAM << "idle\tΣ\t" << std::chrono::nanoseconds (TimedTask::accumulated_idle) << std::endl;
    STD_OSTREAM << "work\tΣ\t" << std::chrono::nanoseconds (TimedTask::accumulated_work) << std::endl;
    STD_OSTREAM << "total\tΣ\t" << total << std::endl;
}

#endif //CONCURRENT_BENCHMARK_H

/* Copyright (C) 2020 Aaron Alef */
