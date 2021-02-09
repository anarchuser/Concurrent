#ifndef CONCURRENT_BENCHMARK_H
#define CONCURRENT_BENCHMARK_H

#include "../config.h"

#include "../lib/helper.h"
#include "../lib/Executor/Executor.h"
#include "../lib/Future/Future.h"
#include "../lib/Task/Task.h"

#include "functions.h"
#include "time.h"

#include <chrono>
#include <iostream>
#include <vector>

void benchmark () {
    auto total = TIME (
            Executor <ITask> executor;

            std::vector <std::shared_ptr <IFuture>> futures;

            /* Fibonacci */
            for (int x = 0; x <= MAX_FIB; x++) {
                Task <unsigned long long> task ([x] { return fibonacci (x); });
                futures.push_back (task.future());
                executor.schedule (std::move (task));
            }

            /* Sleep / Counter */
            for (int x = 0; x < ITERATIONS; x++)
                executor.schedule (Task <void> ([]{ count_to (SLEEP_IN_MS); }));

            for (int x = 0; x < 20; x++) {
                long long fib_x = fibonacci (x);
                auto future = std::dynamic_pointer_cast <Future <unsigned long long>> (futures [x]);
                LOG (INFO) << "fibonacci (" << x << ") = " << fib_x << " (was " << future->await() << ")";
            }
    );
    STD_OSTREAM << "\nthreads\t" << AVAILABLE_THREADS << std::endl;
    STD_OSTREAM << "idle\tΣ\t" << std::chrono::nanoseconds (ITask::idle()) << std::endl;
    STD_OSTREAM << "work\tΣ\t" << std::chrono::nanoseconds (ITask::work()) << std::endl;
    STD_OSTREAM << "total\tΣ\t" << total << std::endl;
}

#endif //CONCURRENT_BENCHMARK_H

/* Copyright (C) 2020 Aaron Alef */
