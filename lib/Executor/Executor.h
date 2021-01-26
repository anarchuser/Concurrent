#ifndef CONCURRENT_EXECUTOR_H
#define CONCURRENT_EXECUTOR_H

#include "../Queue/Queue.h"
#include "Worker/Worker.h"

#include <memory>
#include <thread>

template <typename T>
requires Streamable <T> && Runnable <T>
class Executor {
public:
    Executor() {
        auto _pop = std::function <std::unique_ptr <T>()> ([this]() -> std::unique_ptr <T> { return this->pop(); });
        auto _empty = std::function <bool()> ([this]() -> bool { return this->empty(); });

        for (std::size_t worker = 0; worker < AVAILABLE_THREADS; ++worker)
            workers.template emplace_back (std::make_unique <Worker <T>> (_pop, _empty));
    }
    ~Executor() {
        flush();
        for (auto & worker : workers)
            worker->join();
    }

    void schedule (std::unique_ptr <T> item) {
        queue.push (std::move (item));
    }
    std::unique_ptr <T> pop () {
        if (empty()) LOG (ERROR) << "Tried to pop elements from empty queue!";
        return queue.pop();
    }
    void flush() const {
        await();
    }
    void await() const {
        while (!empty()) std::this_thread::yield();
    }

    [[nodiscard]] bool operator ! () const { return empty(); }
    [[nodiscard]] bool empty () const { return queue.empty (); }
    [[nodiscard]] std::size_t size () const { return queue.size (); }

    [[nodiscard]] std::string toString () const {
        std::stringstream ss;
        ss << "Executor - tasks left: " << size();
        return ss.str();
    }

private:
    std::vector <std::unique_ptr <Worker <T>>> workers;
    Queue <T> queue;
};

#endif //CONCURRENT_EXECUTOR_H

/* Copyright (C) 2020 Aaron Alef */
