#ifndef CONCURRENT_FUTURE_H
#define CONCURRENT_FUTURE_H

#include "IFuture.h"

#include "../helper.h"

#include <atomic>
#include <memory>
#include <thread>

template <typename T>
struct Future : public IFuture {
    Future (std::shared_ptr <T> const item,  std::shared_ptr <std::atomic <bool>> const done): IFuture (done), item {item} {}
    Future (Future const & other): Future (other.item, other.done) {}

    T await() {
        while (!isDone()) std::this_thread::yield();
        return * item;
    }

private:
    std::shared_ptr <T> const item;
};

template <>
struct Future <void>: IFuture {
    explicit Future (std::shared_ptr <std::atomic <bool>> const done): IFuture (done) {}

    void await() const {
        while (!isDone()) std::this_thread::yield();
    }
};

#endif //CONCURRENT_FUTURE_H

/* Copyright (C) 2021 Aaron Alef */
