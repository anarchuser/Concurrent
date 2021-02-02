#ifndef CONCURRENT_MAIN_H
#define CONCURRENT_MAIN_H


#include <iostream>
#include <string>
#include <vector>

void Main() {
    Task <int> ([]() -> int {
        return 10;
    })();
}

#endif //CONCURRENT_MAIN_H

/* Copyright (C) 2020 Aaron Alef */
