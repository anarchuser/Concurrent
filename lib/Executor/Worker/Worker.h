#ifndef CONCURRENT_WORKER_H
#define CONCURRENT_WORKER_H

#include "../../helper.h"
#include "Slave.h"

#include <atomic>
#include <functional>
#include <memory>
#include <thread>

template <Runnable T>
struct Worker {
    Worker (): slave {Slave <T> (shouldStop, [this]() -> std::unique_ptr <T> {
        return this->queue.try_pop();
    })} {}
    ~Worker() {
        await();
        join();
    }

    Worker & operator = (Worker && other) noexcept {
        slave = std::move (other.slave);
        shouldStop = std::move (other.shouldStop);
        return * this;
    }

    void await() {
        while (!empty()) std::this_thread::yield();
    }
    void join() {
        shouldStop = true;
        slave.join();
    }

    void push (std::unique_ptr <T> item) {
        queue.push (std::move (item));
    }
    [[nodiscard]] bool empty () const {
        return queue.empty();
    }
    [[nodiscard]] std::size_t size () const {
        return queue.size();
    }

private:
    std::thread slave;
    Queue <T> queue;

    bool volatile shouldStop = false;
};

#endif //CONCURRENT_WORKER_H

/* Copyright (C) 2020 Aaron Alef */
