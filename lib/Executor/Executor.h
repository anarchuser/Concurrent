#ifndef CONCURRENT_EXECUTOR_H
#define CONCURRENT_EXECUTOR_H

#include "../Queue/Queue.h"
#include "Worker/Worker.h"
#include "../Future/IFuture.h"

#include <memory>
#include <thread>

template <typename T>
requires Streamable <T> && Callable <T>
class Executor {
public:
    Executor() {
        for (std::size_t worker = workers.size(); worker < AVAILABLE_THREADS; ++worker)
            workers.template emplace_back (std::make_unique <Worker <T>>());
    }
    ~Executor() { await(); }

    template <Subclass <T> D>
    std::shared_ptr <IFuture> schedule (D && item) {
        return schedule (std::make_unique <D> (std::forward <D> (item)));
    }
    std::shared_ptr <IFuture> schedule (std::unique_ptr <T> item) {
        auto future = item->future();
        next().push (std::move (item));
        return future;
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
            sum += worker.size();
        return sum;
    }

    [[nodiscard]] std::string toString () const {
        std::stringstream ss;
        ss << "Executor - tasks left: " << size();
        return ss.str();
    }

private:
    static std::vector <std::unique_ptr <Worker <T>>> workers;

    Worker <T> & next () {
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

template <typename T>
requires Streamable <T> && Callable <T>
std::vector <std::unique_ptr <Worker <T>>> Executor <T>::workers = std::vector <std::unique_ptr <Worker <T>>>();

#endif //CONCURRENT_EXECUTOR_H

/* Copyright (C) 2020 Aaron Alef */
