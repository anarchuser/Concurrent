#ifndef CONCURRENT_EXECUTOR_H
#define CONCURRENT_EXECUTOR_H

#include "../Queue/Queue.h"
#include "Worker/Worker.h"
#include "../Future/IFuture.h"
#include "../Task/ITask.h"
#include "../Task/Task.h"

#include <memory>
#include <thread>

class Executor {
public:
    Executor();
    ~Executor();

    template <typename R>
    Future <R> schedule (std::function <R()> && task) {
        auto item = std::make_unique <Task <R>> (std::forward <std::function <R()>> (task));
        auto future = item->future();
        next().push (std::move (item));
        return future;
    }
    void await () const;

    [[nodiscard]] bool operator ! () const;
    [[nodiscard]] bool empty () const;
    [[nodiscard]] std::size_t size () const;

private:
    static std::vector <std::unique_ptr <Worker <ITask>>> workers;

    Worker <ITask> & next ();
};

#endif //CONCURRENT_EXECUTOR_H

/* Copyright (C) 2020 Aaron Alef */
