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

    explicit Container (std::unique_ptr <T> item): Container (std::move <T> (item), nullptr, nullptr) {}
    Container (std::unique_ptr <T> item, Container <T> * prev, Container <T> * next): prev {prev}, next {next} {
        this->item.swap (item);
        if (prev) prev->next = this;
        if (next) next->prev = this;
    }
    Container (Container <T> const &) = delete;
    ~Container() {
        if (prev && prev->next == this) prev->next = next;
        if (next && next->prev == this) next->prev = prev;
    }

    std::unique_ptr <T> unwrap() {
        auto tmp = std::move (item);
        this->~Container();
        return tmp;
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
