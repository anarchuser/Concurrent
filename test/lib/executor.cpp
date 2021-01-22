#include <catch2/catch.hpp>

#include "../../lib/Executor/Executor.h"
#include "../../lib/Task/TimedTask.h"

#include <iostream>
#include <vector>

using namespace std;

SCENARIO ("Executor basic I/O") {
    GIVEN ("A String executor and a list of strings") {
        Executor <TimedTask> executor;
        vector <TimedTask> tasks {
            TimedTask ([] { LOG (INFO) << "task 1/3 successful"; }),
            TimedTask ([] { LOG (INFO) << "task 2/3 successful"; }),
            TimedTask ([] { LOG (INFO) << "task 3/3 successful"; })
        };

        REQUIRE (executor.empty());
        WHEN ("I insert the strings into the executor") {
            for (auto const & s : tasks) {
                REQUIRE_NOTHROW (executor.schedule(s));
                CHECK (executor.empty());
            }
        }
        CHECK_NOTHROW (executor.flush());
        REQUIRE (executor.empty());
    }
}

/* Copyright (C) 2020 Aaron Alef */