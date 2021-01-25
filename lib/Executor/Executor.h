#ifndef CONCURRENT_EXECUTOR_H
#define CONCURRENT_EXECUTOR_H

#include "../Queue/Queue.h"

#include <thread>

template <typename T>
requires Streamable <T> && Runnable <T>
class Executor {
public:
    Executor (std::size_t capacity = 0): capacity {capacity} {};
    ~Executor () {
        flush ();
    }

    void schedule (std::unique_ptr <T> item) {
        queue.push (std::move (item));
        if (size() > capacity)
            execute();
    }

    void execute () {
        (* queue.pop())();
    }

    void flush () {
        while (!empty ()) execute();
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
    std::size_t capacity;

    Queue <T> queue;
};

#endif //CONCURRENT_EXECUTOR_H

/* Copyright (C) 2020 Aaron Alef */
