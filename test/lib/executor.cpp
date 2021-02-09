#include <catch2/catch.hpp>

#include "../../lib/Executor/Executor.h"
#include "../../lib/Task/Task.h"

#include <iostream>
#include <vector>

using namespace std;

SCENARIO ("Executor basic I/O") {
    GIVEN ("A list of strings") {
        Executor executor;

        REQUIRE (executor.empty());
        WHEN ("I insert the strings into the executor") {
            CHECK_NOTHROW (executor.schedule <void> ([] { LOG (INFO) << "task 1/3 successful"; }));
            CHECK_NOTHROW (executor.schedule <void> ([] { LOG (INFO) << "task 2/3 successful"; }));
            CHECK_NOTHROW (executor.schedule <void> ([] { LOG (INFO) << "task 3/3 successful"; }));
        }
        CHECK_NOTHROW (executor.await());
        REQUIRE (executor.empty());
    }
    GIVEN ("A few simple tasks") {
        Executor executor;
        for (int x = -20; x < 20; x+= 4)
            CHECK (executor.schedule <int> ([x] {
                std::this_thread::sleep_for (std::chrono::milliseconds (500));
                return x;
            }).await() == x);
    }
}

/* Copyright (C) 2020 Aaron Alef */
