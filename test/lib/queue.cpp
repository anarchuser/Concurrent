#include <catch2/catch.hpp>
#include "../../lib/Queue/Queue.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

SCENARIO ("Queue basic I/O") {
    GIVEN ("A String queue and a list of strings") {
        Queue <string> queue;
        vector <string> elements { "test", "abcde", "pppppppp", "xyz" };

        REQUIRE (queue.empty());
        WHEN ("I insert the strings into the queue") {
            for (auto const & s : elements) {
                REQUIRE_NOTHROW (queue.push (make_unique <string> (s)));
            }

            THEN ("The size grows accordingly") {
                CHECK (queue.size() == elements.size());
            }

            THEN ("I can remove elements from the queue") {
                CHECK (queue.size() == elements.size());

                for (auto const & s : elements) {
                    CHECK (* queue.pop () == s);
                }
                CHECK (queue.empty());
            }
        }
        CHECK_NOTHROW (queue.flush());
        REQUIRE (queue.empty());
        size_t idx = 0;
        for (auto const & s : elements) {
            CHECK (queue.empty());
            REQUIRE_NOTHROW (queue.push (make_unique <string> (s)));
            CHECK (queue.size() == 1);
            REQUIRE_NOTHROW (elements [idx++] == * queue.pop());
        }
        CHECK (queue.empty());
    }
}

/* Copyright (C) 2020 Aaron Alef */
