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

    Task & operator = (Task && other) {
        task   = std::move (other.task);
        ctor   = other.ctor;
        start  = other.start;
        end    = other.end;
        dtor   = other.dtor;
        result = other.result;
        done   = other.done;
        return * this;
    }

    void operator ()() override {
        if (run) await();
        else {
            run = true;
            start = std::chrono::high_resolution_clock::now();
            * result = task();
            * done = true;
            end = std::chrono::high_resolution_clock::now();
        }
    }
    std::shared_ptr <R> await() const {
        while (!isDone()) std::this_thread::yield();
        return result;
    }
    Future <R> future() const {
        return Future <R> (result, done);
    }

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
            task {std::forward <std::function <void()>> (task)} {
        ctor = std::chrono::high_resolution_clock::now();
    }

    Task (Task const & other) = delete;
    Task (Task && other) noexcept { * this = std::move (other); }

    Task & operator = (Task && other)  noexcept {
        task   = std::move (other.task);
        ctor   = other.ctor;
        start  = other.start;
        end    = other.end;
        dtor   = other.dtor;
        done   = other.done;
        return * this;
    }

    void operator () () {
        if (run) return await();
        else {
            run = true;
            start = std::chrono::high_resolution_clock::now();
            task();
            * done = true;
            end = std::chrono::high_resolution_clock::now();
        }
    }
    void await() const {
        while (!isDone()) std::this_thread::yield();
    }

private:
    std::function <void()> task;
};


#endif //CONCURRENT_TASK_H

/* Copyright (C) 2021 Aaron Alef */
