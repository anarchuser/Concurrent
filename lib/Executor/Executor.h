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
    Executor() {
        for (std::size_t worker = workers.size(); worker < AVAILABLE_THREADS; ++worker)
            workers.template emplace_back (std::make_unique <Worker <ITask>>());
    }
    ~Executor() { await(); }

    template <typename R>
    Future <R> schedule (std::function <R()> && task) {
        auto item = std::make_unique <Task <R>> (std::forward <std::function <R()>> (task));
        auto future = std::move (item->future);
        next().push (std::move (item));
        return std::move (future);
    }
    void await() const {
        while (!empty()) std::this_thread::yield();
    }

    [[nodiscard]] bool operator ! () const { return empty(); }
    [[nodiscard]] bool empty () const {
        for (auto const & worker : workers)
            if (!worker->empty())
                return false;
        return true;
    }
    [[nodiscard]] std::size_t size () const {
        std::size_t sum = 0;
        for (auto const & worker : workers)
            sum += worker->size();
        return sum;
    }

    [[nodiscard]] std::string toString () const {
        std::stringstream ss;
        ss << "Executor - tasks left: " << size();
        return ss.str();
    }

private:
    static std::vector <std::unique_ptr <Worker <ITask>>> workers;

    Worker <ITask> & next () {
        std::size_t min = -1;
        std::size_t min_idx;
        for (std::size_t idx = 0; idx < AVAILABLE_THREADS; ++idx) {
            if (workers [idx]->size() < min) {
                min = workers [idx]->size();
                min_idx = idx;
            }
        }
        return * workers [min_idx];
    }
};

std::vector <std::unique_ptr <Worker <ITask>>> Executor::workers = std::vector <std::unique_ptr <Worker <ITask>>>();

#endif //CONCURRENT_EXECUTOR_H

/* Copyright (C) 2020 Aaron Alef */
