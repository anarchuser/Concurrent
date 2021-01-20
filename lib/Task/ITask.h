#ifndef CONCURRENT_ITASK_H
#define CONCURRENT_ITASK_H

#include <thread>

struct ITask {
    virtual void operator () () = 0;
    virtual bool operator ! () const = 0;

    void await() const {
       while (! * this) std::this_thread::yield();
    }
};

#endif //CONCURRENT_ITASK_H

/* Copyright (C) 2020 Aaron Alef */
