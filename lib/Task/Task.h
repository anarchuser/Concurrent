#ifndef CONCURRENT_TASK_H
#define CONCURRENT_TASK_H

#include "ITask.h"

#include <atomic>
#include <functional>
#include <string>

class Task: ITask {
public:
    const int ID = ID_counter++;

    explicit Task (std::function <void()> task): task {std::move (task)} { ++ID_counter; }

    virtual void operator () () override {
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
        ss << "T: " << ((done) ? "done" : (run) ? "running" : "idle");
        return ss.str();
    }

private:
    static std::atomic <int> ID_counter;

    std::function <void()> task;

    bool run = false;
    bool done = false;
};

std::atomic <int> Task::ID_counter = 0;

std::ostream & operator << (std::ostream & os, Task const & task) {
    return os << task.toString();
}

#endif //CONCURRENT_TASK_H

/* Copyright (C) 2020 Aaron Alef */
