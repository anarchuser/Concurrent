#ifndef CONCURRENT_TASK_H
#define CONCURRENT_TASK_H

#include "ITask.h"

#include "../Future/Future.h"

#include <atomic>
#include <functional>


template <typename R>
class Task: public ITask {
public:
    explicit Task (std::function <R()> && task): task {std::forward <std::function <R()>> (task)} {}
    Task (Task const & other) = delete;
    Task (Task && other) { * this = std::move (other); }

    Task & operator = (Task && other) {
        task = std::move (other.task);
        result = other.result;
        done = other.done;
        return * this;
    }
    std::shared_ptr <R> operator () () {
        if (run) return await();
        run = true;
        * result = task();
        * done = true;
        return result;
    }
    std::shared_ptr <R> await() const {
        while (!isDone()) std::this_thread::yield();
        return result;
    }
    Future <R> getResult() const {
        return Future <R> (result, done);
    }

private:
    std::function <R()> task;
    std::shared_ptr <R> result = std::make_shared <R>();
};

#endif //CONCURRENT_TASK_H

/* Copyright (C) 2021 Aaron Alef */
