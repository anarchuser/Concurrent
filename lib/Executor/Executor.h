#ifndef CONCURRENT_EXECUTOR_H
#define CONCURRENT_EXECUTOR_H

#include "../Queue/Queue.h"

#include <thread>

template <typename T>
requires Streamable <T> && Runnable <T>
class Executor {
public:
    ~Executor () { flush (); }

    void schedule (std::unique_ptr <T> item) {
        queue.push (std::move (item));
        execute();
    }

    void execute () {
        threads.template emplace_back(std::move (* queue.pop()));
    }

    void flush () {
        while (!empty ()) execute();
        for (auto & thread : threads)
            thread.join();
        threads.clear();
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
    std::vector <std::thread> threads;

    Queue <T> queue;
};

#endif //CONCURRENT_EXECUTOR_H

/* Copyright (C) 2020 Aaron Alef */
