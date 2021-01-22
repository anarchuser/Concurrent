#ifndef CONCURRENT_TIMEDTASK_H
#define CONCURRENT_TIMEDTASK_H

#include "Task.h"

#include "../helper.h"

#include <chrono>
#include <thread>

class TimedTask: public Task {
public:
    TimedTask (std::function <void()> task): Task (task), ctor {std::chrono::high_resolution_clock::now()} {}
    ~TimedTask () {
        dtor = std::chrono::high_resolution_clock::now();
        LOG (INFO) <<
                "Task #"     << Task::ID <<
                " Thread #" << std::this_thread::get_id() <<
                " ctor "    << ctor     <<
                " start "   << start    <<
                " end "     << end      <<
                " dtor "    << dtor     <<
                " idle "    << (start - ctor)  <<
                " work "    << (end   - start) <<
                " linger "  << (dtor  - end);
    }

    virtual void operator () () override {
        start = std::chrono::high_resolution_clock::now();
        Task::operator()();
        end = std::chrono::high_resolution_clock::now();
    }

private:
    std::chrono::time_point <std::chrono::high_resolution_clock> ctor, start, end, dtor;

};

#endif //CONCURRENT_TIMEDTASK_H

/* Copyright (C) 2020 Aaron Alef */
