#ifndef CONCURRENT_EXECUTOR_H
#define CONCURRENT_EXECUTOR_H

#include "../Queue/Queue.h"
#include "../Task/Task.h"

class Executor: public Queue <Task> {
public:
    void schedule (Task item) {
        push (std::move (item));
    }

private:
    virtual void push (Task item) override {
        Queue::push (std::move (item));
        pop ()();
    }

    virtual Task pop() override {
        return Queue::pop();
    }
};

#endif //CONCURRENT_EXECUTOR_H

/* Copyright (C) 2020 Aaron Alef */
