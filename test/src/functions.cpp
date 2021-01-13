#include <catch2/catch.hpp>
#include "../../src/functions.h"

TEST_CASE ("Fibonacci sequence algorithm") {
    CHECK (fibonacci (30) == 832040);
}

/* Copyright (C) 2020 Aaron Alef */
