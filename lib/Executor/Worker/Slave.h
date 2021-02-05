#ifndef CONCURRENT_SLAVE_H
#define CONCURRENT_SLAVE_H

#include "../../helper.h"

#include <memory>
#include <thread>
#include <functional>

template <Runnable T>
struct Slave {
    Slave (std::atomic <bool> const & stop, std::function <std::unique_ptr <T>()> pop):
            stop {stop},
            pop {std::move (pop)} {}

    void operator () () {
        while (!stop) {
            auto task = pop();
            if (task) {
                (std::cout << '.').flush();
                (* task)();
            }
            else std::this_thread::yield();
        }
    }

private:
    std::atomic <bool> const & stop;

    std::function <std::unique_ptr <T>()> pop;
};

#endif //CONCURRENT_SLAVE_H

/* Copyright (C) 2020 Aaron Alef */
