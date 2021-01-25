#ifndef CONCURRENT_TASK_H
#define CONCURRENT_TASK_H

#include "ITask.h"

#include <atomic>
#include <functional>

class Task: public ITask {
public:
    explicit Task (std::function <void()> && task): task {std::forward <std::function <void()>> (task)} {}
    Task (Task const & other) = delete;
    Task (Task && other) { * this = std::move (other); }

    Task & operator = (Task && other) {
        task = std::move (other.task);
        run = other.run;
        done = other.done;
        return * this;
    }

    void operator () () override {
        if (run) return await();
        run = true;
        task();
        done = true;
    }

private:
    std::function <void()> task;
};

#endif //CONCURRENT_TASK_H

/* Copyright (C) 2020 Aaron Alef */
