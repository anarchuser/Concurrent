#ifndef CONCURRENT_TIMEDTASK_H
#define CONCURRENT_TIMEDTASK_H

#include "../../config.h"

#include "Task.h"

#include "../helper.h"

#include <chrono>
#include <thread>

class TimedTask: public ITask {
public:
    explicit TimedTask (std::function <void()> && task):
            task {std::make_unique <std::function <void()>> (std::move (task))},
            ctor {std::chrono::high_resolution_clock::now()} {}
    TimedTask (TimedTask const & other) = delete;
    TimedTask (TimedTask && other) noexcept {
        * this = std::move (other);
    }
    ~TimedTask () {
        if (!done) return;
        dtor = std::chrono::high_resolution_clock::now();
        LOG (INFO) <<
                "Task #"    << ID <<
                " Pointer " << this <<
                " Thread #" << std::this_thread::get_id() <<
                " ctor "    << ctor     <<
                " start "   << start    <<
                " end "     << end      <<
                " dtor "    << dtor     <<
                " idle "    << (start - ctor)  <<
                " work "    << (end   - start) <<
                " linger "  << (dtor  - end)   <<
                " total "   << (dtor  - ctor);
    }

    TimedTask & operator = (TimedTask && other) {
        LOG (WARNING) << "Move Task #" << other.ID << " to Task #" << ID;

        task = std::move (other.task);
        run = other.run;
        done = other.done;
        ctor  = other.ctor;
        start = other.start;
        end   = other.end;
        dtor  = other.dtor;
        return * this;
    }

    virtual void operator () () override {
        if (run) return await();
        run = true;
        start = std::chrono::high_resolution_clock::now();
        (* task) ();
        done = true;
        end = std::chrono::high_resolution_clock::now();
    }

private:
    std::unique_ptr <std::function <void()>> task;

    std::chrono::time_point <std::chrono::high_resolution_clock> ctor, start, end, dtor;
};

std::unique_ptr <TimedTask> timedTaskOf (std::function <void()> && task);

#endif //CONCURRENT_TIMEDTASK_H

/* Copyright (C) 2020 Aaron Alef */
