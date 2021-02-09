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
            task {std::forward <std::function <R()>> (task)} {
        _future = std::make_shared <Future <R>> (result, done);
    }
    Task (Task const & other) = delete;
    Task (Task && other) noexcept { * this = std::move (other); }

    Task & operator = (Task && other) {
        task    = std::move (other.task);
        _future = std::move (other._future);
        ctor    = other.ctor;
        start   = other.start;
        end     = other.end;
        result  = other.result;
        done    = other.done;
        return  * this;
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

private:
    void await() {
        while (!isDone()) std::this_thread::yield();
    }

    std::function <R()> task;
    std::shared_ptr <R> result = std::make_shared <R>();
};

/** Task without return value */
template <>
class Task <void>: public ITask {
public:
    explicit Task (std::function <void()> && task):
            task {std::forward <std::function <void()>> (task)} {
        ctor = std::chrono::high_resolution_clock::now();
        _future = std::make_shared <Future <void>> (done);
    }

    Task (Task const & other) = delete;
    Task (Task && other) noexcept { * this = std::move (other); }

    Task & operator = (Task && other)  noexcept {
        task    = std::move (other.task);
        _future = std::move (other._future);
        ctor    = other.ctor;
        start   = other.start;
        end     = other.end;
        done    = other.done;
        return  * this;
    }

    void operator () () override {
        if (run) await();
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
