#ifndef CONCURRENT_FUTURE_H
#define CONCURRENT_FUTURE_H

#include <thread>

struct IFuture {
    virtual ~IFuture() = 0;
};

#endif //CONCURRENT_FUTURE_H

/* Copyright (C) 2020 Aaron Alef */
