#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include "../../config.h"

#include "Container/Container.h"
#include "../helper.h"

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

    virtual void push (std::unique_ptr <T> item) {
        back = new Container <T> (std::move (item), back, nullptr);
        if (empty()) front = back;
        ++count;
    }
    virtual std::unique_ptr <T> pop () {
        if (empty ()) THROW (std::logic_error ("Cannot pop elements from empty queue!"));
        auto tmp = front;
        front = front->next;
        if (count <= 1) back = front;
        auto item = tmp->unwrap();
        --count;
        delete tmp;
        return std::move (item);
    }
    virtual void flush () { while (count) pop (); }
    virtual bool empty () const { return !count; }
    virtual std::size_t size () const { return  count; }

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
    std::size_t count = 0;
};

template <Streamable T>
std::ostream & operator << (std::ostream & os, Queue<T> const & queue) {
    return os << queue.toString ();
}

#endif //CONCURRENT_QUEUE_H

/* Copyright (C) 2020 Aaron Alef */
