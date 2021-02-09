#ifndef CONCURRENT_IFUTURE_H
#define CONCURRENT_IFUTURE_H

#include <thread>

struct IFuture {
    virtual ~IFuture() = 0;

    virtual bool isDone() const = 0;
};

#endif //CONCURRENT_IFUTURE_H

/* Copyright (C) 2020 Aaron Alef */
