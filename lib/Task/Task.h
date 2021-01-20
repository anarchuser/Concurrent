#ifndef CONCURRENT_TASK_H
#define CONCURRENT_TASK_H

#include "ITask.h"

#include <functional>

class Task: ITask {
public:
    explicit Task (std::function <void()> task): task {std::move (task)} {}

    void operator () () override {
        if (run) return await();
        run = true;
        return task();
    }
    bool operator ! () const override {
        return done;
    }

private:
    std::function <void()> task;

    bool run = false;
    bool done = false;
};


#endif //CONCURRENT_TASK_H

/* Copyright (C) 2020 Aaron Alef */
