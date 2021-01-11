#ifndef CONCURRENT_HELPERS_H
#define CONCURRENT_HELPERS_H

#include <chrono>
#include <ostream>
#include <iostream>

std::ostream & operator << (std::ostream & os, std::chrono::microseconds us);

void test();

#endif //CONCURRENT_HELPERS_H

/* Copyright (C) 2020 Aaron Alef */
