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
    Worker (std::function <std::unique_ptr <T>()> pop):
             slave {Slave (shouldStop, std::move (pop))} {}
    ~Worker() { join(); }

    Worker & operator = (Worker && other) noexcept {
        slave = std::move (other.slave);
        shouldStop = std::move (other.shouldStop);
        return * this;
    }

    void join() {
        shouldStop = true;
        slave.join();
    }

private:
    std::thread slave;

    bool volatile shouldStop = false;
};

#endif //CONCURRENT_WORKER_H

/* Copyright (C) 2020 Aaron Alef */
