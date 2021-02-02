#ifndef CONCURRENT_FUTURE_H
#define CONCURRENT_FUTURE_H

#include "IFuture.h"

#include "../helper.h"

#include <memory>
#include <thread>

template <Streamable T>
class Future : IFuture {
    explicit Future (std::shared_ptr <T> const item): item {item} {}
    Future (Future const & other): Future (other.item) {}

    std::shared_ptr <T> await() const {
        while (!done()) std::this_thread::yield();
        return item;
    }
    [[nodiscard]] bool done() const {
        return item != nullptr;
    }
    [[nodiscard]] bool operator ! const {
        return done();
    }

private:
    std::shared_ptr <T> const volatile item;
};

#endif //CONCURRENT_FUTURE_H

/* Copyright (C) 2020 Aaron Alef */
