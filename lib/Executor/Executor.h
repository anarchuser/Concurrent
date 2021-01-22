#ifndef CONCURRENT_EXECUTOR_H
#define CONCURRENT_EXECUTOR_H

#include "../Queue/Queue.h"

template <Runnable T>
class Executor: protected Queue <T> {
public:
    Executor (): Queue<T>() {};
    ~Executor () {
        flush ();
    }

    void schedule (T const & item) {
        Queue <T>::push (item);
        Queue <T>::pop ()();
    }

    void flush () { while (!empty()) Queue <T>::pop ()(); }
    [[nodiscard]] bool empty () const { return Queue <T>::empty(); }
    [[nodiscard]] std::size_t size () const { return Queue <T>::size(); }

    [[nodiscard]] std::string toString () const {
        std::stringstream ss;
        ss << "Executor - tasks left: " << size();
        return ss.str();
    }
};

#endif //CONCURRENT_EXECUTOR_H

/* Copyright (C) 2020 Aaron Alef */
