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
        accumulated_idle += (start - ctor).count();
        accumulated_work += (end  - start).count();
        STD_OSTREAM <<
                "Task ID "    << ID <<
                "\tPointer " << this <<
                "\tThread #" << std::this_thread::get_id() <<
                "\tctor "    << ctor     <<
                "\tstart "   << start    <<
                "\tend "     << end      <<
                "\tdtor "    << dtor     <<
                "\tidle "    << (start - ctor)  <<
                "\twork "    << (end   - start) <<
                "\tlinger "  << (dtor  - end)   <<
                "\ttotal "   << (dtor  - ctor) << std::endl;
    }

    TimedTask & operator = (TimedTask && other) {
        task = std::move (other.task);
        ctor  = other.ctor;
        start = other.start;
        end   = other.end;
        dtor  = other.dtor;
        return * this;
    }

    void operator () () {
        if (run) return await();
        run = true;
        start = std::chrono::high_resolution_clock::now();
        (* task) ();
        * done = true;
        end = std::chrono::high_resolution_clock::now();
    }
    void await() const {
        while (!isDone()) std::this_thread::yield();
    }

    static std::atomic <std::size_t> accumulated_idle;
    static std::atomic <std::size_t> accumulated_work;

private:
    std::unique_ptr <std::function <void()>> task;

    std::chrono::time_point <std::chrono::high_resolution_clock> ctor, start, end, dtor;
};

std::atomic <std::size_t> TimedTask::accumulated_idle = 0;
std::atomic <std::size_t> TimedTask::accumulated_work = 0;

std::unique_ptr <TimedTask> timedTaskOf (std::function <void()> && task);

#endif //CONCURRENT_TIMEDTASK_H

/* Copyright (C) 2021 Aaron Alef */
