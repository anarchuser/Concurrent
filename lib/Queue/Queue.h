#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include "Container/Container.h"
#include "../helper.h"

#include "../../config.h"

#include <sstream>
#include <vector>

#include <iostream>

template <Streamable T>
struct Queue {
public:
    Queue() = default;
    ~Queue() { flush(); }

    void push (T item) {
        back = new Container <T> (std::move (item), back, nullptr);
        if (empty()) front = back;
        ++count;
    }
    T pop () {
        if (empty()) THROW (std::logic_error ("Cannot pop elements from empty queue!"));
        auto tmp = front;
        front = front->next;
        if (count <= 1) back = front;
        T item = * tmp->reap();
        --count;
        delete tmp;
        return std::move (item);
    }
    void flush() {
        while (count) pop();
    }
    bool empty () const { return !count; }
    std::size_t size () const { return  count; }

    std::string toString () const {
        std::stringstream ss;
        Container <T> * trav = front;
        while (trav) {
            ss << "<" << * trav;
            if (trav == back) break;
            std::cout << trav->next;
            trav = trav->next;
        }
        ss << "<";
        return ss.str();
    }

private:
    Container <T> * front = nullptr;  // Where elements are removed from
    Container <T> * back  = nullptr;  // Where elements are added to
    std::size_t count = 0;
};

template <Streamable T>
std::ostream & operator << (std::ostream & os, Queue<T> const & queue) {
    return os << queue.toString();
}

#endif //CONCURRENT_QUEUE_H

/* Copyright (C) 2020 Aaron Alef */
