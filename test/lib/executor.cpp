#include <catch2/catch.hpp>

#include "../../lib/Executor/Executor.h"
#include "../../lib/Task/Task.h"

#include <iostream>
#include <vector>

using namespace std;

SCENARIO ("Executor basic I/O") {
    GIVEN ("A String executor and a list of strings") {
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
}

/* Copyright (C) 2020 Aaron Alef */
