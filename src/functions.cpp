#include "functions.h"

unsigned long long fibonacci (unsigned long long index) {
    return (index <= 1) ? index : fibonacci (index - 1) + fibonacci (index - 2);
}

/* Copyright (C) 2020 Aaron Alef */
