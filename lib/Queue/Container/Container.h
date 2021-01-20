#ifndef CONCURRENT_CONTAINER_H
#define CONCURRENT_CONTAINER_H

#include "../../helper.h"

#include <memory>
#include <utility>

template <Streamable T>
struct Container {
public:
    Container <T> * prev = nullptr;  // Points to element added most previously
    Container <T> * next = nullptr;  // Points to element added afterwards

    explicit Container (T item): Container (item, nullptr, nullptr) {}
    Container (T item, Container <T> * prev, Container <T> * next):
            item {std::make_unique <T> (item)}, prev {prev}, next {next} {
        if (prev) prev->next = this;
        if (next) next->prev = this;
    }
    Container (Container <T> const &) = delete;
    ~Container() {
        if (prev && prev->next == this) prev->next = next;
        if (next && next->prev == this) next->prev = prev;
    }

    std::unique_ptr <T> reap() {
        return std::move (item);
    }

    T const & peak() const {
        return * item;
    }

private:
    std::unique_ptr <T> item;

};

template <Streamable T>
std::ostream & operator << (std::ostream & os, Container <T> const & c) {
    return os << "[" << c.peak() << "]";
}


#endif //CONCURRENT_CONTAINER_H

/* Copyright (C) 2020 Aaron Alef */
