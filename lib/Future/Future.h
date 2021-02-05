#ifndef CONCURRENT_FUTURE_H
#define CONCURRENT_FUTURE_H

#include "IFuture.h"

#include "../helper.h"

#include <atomic>
#include <memory>
#include <thread>

template <Streamable T>
struct Future : IFuture {
    explicit Future (std::shared_ptr <T> const item,  std::shared_ptr <std::atomic <bool>> const done): item {item}, done {done} {}
    Future (Future const & other): Future (other.item, other.done) {}

    T await() {
        while (!isDone()) std::this_thread::yield();
        return * item;
    }
    [[nodiscard]] virtual bool isDone() const override {
        return * done;
    }
    [[nodiscard]] bool operator !() const {
        return * done;
    }

private:
    std::shared_ptr <T> const item;
    std::shared_ptr <std::atomic <bool>> const done;
};

#endif //CONCURRENT_FUTURE_H

/* Copyright (C) 2021 Aaron Alef */
