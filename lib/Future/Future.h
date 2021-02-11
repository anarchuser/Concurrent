#ifndef CONCURRENT_FUTURE_H
#define CONCURRENT_FUTURE_H

#include "IFuture.h"

#include "../helper.h"

#include <atomic>
#include <memory>
#include <thread>

template <typename T>
struct Future : public IFuture {
    Future (std::shared_ptr <T> const item, std::shared_ptr <std::atomic <bool>> const done): IFuture (done), item {item} {}
    Future (Future const & other) = delete;
    Future (Future && other): IFuture (std::move (other)), item {other.item} {}

    Future & operator = (Future && other) noexcept {
        item = other.item;
        return * this;
    }

    T await() const {
        while (!isDone()) std::this_thread::yield();
        return * item;
    }

private:
    std::shared_ptr <T> item;
};

template <>
struct Future <void>: IFuture {
    explicit Future (std::shared_ptr <std::atomic <bool>> const done): IFuture (done) {}

    void await() const {
        while (!isDone()) std::this_thread::yield();
    }
};

template <Streamable T>
std::ostream & operator << (std::ostream & os, Future <T> const & future) {
    return os << future.await();
}

#endif //CONCURRENT_FUTURE_H

/* Copyright (C) 2021 Aaron Alef */
