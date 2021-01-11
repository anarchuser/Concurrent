#include "functions.h"

unsigned long long fibonacci (unsigned long long index) {
    return (index <= 1) ? index : fibonacci (index - 1) + fibonacci (index - 2);
}

int count_to (int number) {
    for (int x = 0; x < number; ++x)
        std::this_thread::sleep_for (std::chrono::milliseconds (1));
    return number;
}

/* Copyright (C) 2020 Aaron Alef */
