#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include "../../config.h"

#include "Container/Container.h"
#include "../helper.h"

#include <atomic>
#include <mutex>
#include <sstream>
#include <vector>

#include <iostream>

template <Streamable T>
struct Queue {
public:
    Queue () = default;
    Queue (Queue const & other) = delete;
    Queue (Queue && other) = delete;
    ~Queue () { flush(); }

    void push (T && item) {
        push (std::make_unique <T> (std::move (item)));
    }
    void push (std::unique_ptr <T> item) {
        auto tmp = new Container <T> (std::move (item));
        {
            std::lock_guard guard (mx);

            tmp->prev = back;
            if (empty()) front = tmp;
            else back->next = tmp;
            back = tmp;
        }
        ++count;
    }
    /** Pops the oldest element from the queue. Throws if empty. */
    std::unique_ptr <T> pop () {
        auto item = try_pop();
        if (item) return item;
        THROW (std::logic_error ("Cannot pop elements from empty queue!"));
    }
    /** Pops the oldest element from the queue. Returns empty pointer if empty. */
    std::unique_ptr <T> try_pop () {
        Container <T> * tmp;
        {
            std::lock_guard guard(mx);

            if (empty()) return nullptr;
            tmp = front;
            front = front->next;
            if (size() <= 2) back = front;
            --count;
        }
        auto item = tmp->unwrap();
        delete tmp;
        return std::move (item);
    }
    void flush () {
        while (try_pop());
    }
    bool empty () const {
        return !back;
    }
    std::size_t size () const { return count; }

    virtual std::string toString () const {
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
    std::atomic <int> count = 0;

    mutable std::mutex mx;
};

template <Streamable T>
std::ostream & operator << (std::ostream & os, Queue<T> const & queue) {
    return os << queue.toString ();
}

#endif //CONCURRENT_QUEUE_H

/* Copyright (C) 2020 Aaron Alef */
