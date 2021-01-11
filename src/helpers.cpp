#include "helpers.h"

std::ostream & operator << (std::ostream & os, std::chrono::microseconds us) {
    return os << us.count() << " μs";
}

void test() {
    std::cout << "hi!" << std::endl;
}

/* Copyright (C) 2020 Aaron Alef */
