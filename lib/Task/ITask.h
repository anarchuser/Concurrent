#ifndef CONCURRENT_ITASK_H
#define CONCURRENT_ITASK_H

#include <string>
#include <thread>

struct ITask {
    virtual void operator () () = 0;
    virtual bool operator ! () const = 0;
    virtual std::string toString () const = 0;

    void await() const {
       while (! * this) std::this_thread::yield();
    }
};

std::ostream & operator << (std::ostream & os, ITask const & task) {
    return os << task.toString();
}

#endif //CONCURRENT_ITASK_H

/* Copyright (C) 2020 Aaron Alef */
