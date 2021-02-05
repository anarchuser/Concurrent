#ifndef CONCURRENT_TASK_H
#define CONCURRENT_TASK_H

#include "../../config.h"

#include "ITask.h"

#include "../Future/Future.h"
#include "../helper.h"

#include <atomic>
#include <chrono>
#include <functional>
#include <thread>
#include <type_traits>

/** Task returning a value */
template <typename R>
class Task: public ITask {
public:
    explicit Task (std::function <R()> && task):
            task {std::forward <std::function <R()>> (task)},
            ctor {std::chrono::high_resolution_clock::now()} {}
    Task (Task const & other) = delete;
    Task (Task && other) noexcept { * this = std::move (other); }
    ~Task () {
        if (end <= start) return;
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

    Task & operator = (Task && other) {
        task = std::move (other.task);
        ctor  = other.ctor;
        start = other.start;
        end   = other.end;
        dtor  = other.dtor;
        result = other.result;
        done = other.done;
        return * this;
    }

    std::shared_ptr <R> operator () () {
        if (run) return await();
        run = true;
        start = std::chrono::high_resolution_clock::now();
        * result = task();
        * done = true;
        end = std::chrono::high_resolution_clock::now();
        return result;
    }
    std::shared_ptr <R> await() const {
        while (!isDone()) std::this_thread::yield();
        return result;
    }

    static std::atomic <std::size_t> accumulated_idle;
    static std::atomic <std::size_t> accumulated_work;

private:
    std::function <R()> task;
    std::shared_ptr <R> result = std::make_shared <R>();

    std::chrono::time_point <std::chrono::high_resolution_clock> ctor, start, end, dtor;
};

/** Task without return value */
template <>
class Task <void>: public ITask {
public:
    explicit Task (std::function <void()> && task):
            task {std::forward <std::function <void()>> (task)},
            ctor {std::chrono::high_resolution_clock::now()} {}
    Task (Task const & other) = delete;
    Task (Task && other) noexcept { * this = std::move (other); }
    ~Task () {
        if (end <= start) return;
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

    Task & operator = (Task && other)  noexcept {
        task = std::move (other.task);
        ctor  = other.ctor;
        start = other.start;
        end   = other.end;
        dtor  = other.dtor;
        done = other.done;
        return * this;
    }

    void operator () () {
        if (run) return await();
        run = true;
        start = std::chrono::high_resolution_clock::now();
        task();
        * done = true;
        end = std::chrono::high_resolution_clock::now();
    }
    void await() const {
        while (!isDone()) std::this_thread::yield();
    }

    static std::atomic <std::size_t> accumulated_idle;
    static std::atomic <std::size_t> accumulated_work;

private:
    std::function <void()> task;

    std::chrono::time_point <std::chrono::high_resolution_clock> ctor, start, end, dtor;
};

template <typename R>
std::atomic <std::size_t> Task <R>::accumulated_idle = 0;
std::atomic <std::size_t> Task <void>::accumulated_idle = 0;
template <typename R>
std::atomic <std::size_t> Task <R>::accumulated_work = 0;
std::atomic <std::size_t> Task <void>::accumulated_work = 0;


#endif //CONCURRENT_TASK_H

/* Copyright (C) 2021 Aaron Alef */
