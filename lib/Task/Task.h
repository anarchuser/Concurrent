#ifndef CONCURRENT_TASK_H
#define CONCURRENT_TASK_H

#include "ITask.h"

#include <functional>
#include <string>

class Task: ITask {
public:
    explicit Task (std::function <void()> task): task {std::move (task)} {}

    void operator () () override {
        if (run) return await();
        run = true;
        task();
        done = true;
    }
    bool operator ! () const override {
        return done;
    }

    std::string toString () const override {
        std::stringstream ss;
        ss << "T: " << (done) ? "done" : (run) ? "running" : "idle";
        return ss.str();
    }

private:
    std::function <void()> task;

    bool run = false;
    bool done = false;
};

std::ostream & operator << (std::ostream & os, Task const & task) {
    return os << task.toString();
}

#endif //CONCURRENT_TASK_H

/* Copyright (C) 2020 Aaron Alef */
