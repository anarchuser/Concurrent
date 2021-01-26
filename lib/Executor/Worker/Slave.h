#ifndef CONCURRENT_SLAVE_H
#define CONCURRENT_SLAVE_H

#include "../../helper.h"

#include <memory>
#include <thread>
#include <functional>

template <Runnable T>
struct Slave {
    Slave (bool volatile const & stop,
                    std::function <std::unique_ptr <T>()> pop,
                    std::function <bool()> empty):
            stop {stop},
            pop {std::move (pop)},
            empty {std::move (empty)} {}

    void operator () () {
        while (!stop) {
            if (empty ()) std::this_thread::yield ();
            else (* pop ())();
        }
    }

private:
    bool volatile const & stop;

    std::function <std::unique_ptr <T>()> pop;
    std::function <bool()> const empty;
};

#endif //CONCURRENT_SLAVE_H

/* Copyright (C) 2020 Aaron Alef */
