#ifndef CONCURRENT_ITASK_H
#define CONCURRENT_ITASK_H

#include "../../config.h"

#include "../helper.h"

#include <functional>
#include <sstream>
#include <string>
#include <thread>

struct ITask {
public:
    ~ITask() {
//        if (end <= start) return;
        dtor = std::chrono::high_resolution_clock::now();
        accumulated_idle += (start - ctor).count();
        accumulated_work += (end  - start).count();
        STD_OSTREAM <<
                    "Task ID "    << ID <<
                    "\tPointer " << this <<
                    "\tThread #" << std::this_thread::get_id() <<
                    "\tctor "    << ctor     <<
                    "\tstart "   << start    <<
                    "\tend "     << end      <<
                    "\tdtor "    << dtor     <<
                    "\tidle "    << (start - ctor)  <<
                    "\twork "    << (end   - start) <<
                    "\tlinger "  << (dtor  - end)   <<
                    "\ttotal "   << (dtor  - ctor) << std::endl;
    }

    const int ID = ID_ctr++;

    virtual void operator ()() = 0;
    [[nodiscard]] virtual bool operator ! () const;
    [[nodiscard]] virtual bool isDone () const;
    [[nodiscard]] virtual bool isRunning () const;

    [[nodiscard]] virtual std::string toString () const;

    static std::size_t idle() {
        return accumulated_idle;
    }
    static std::size_t work() {
        return accumulated_work;
    }

protected:
    std::atomic <bool> run = false;
    std::shared_ptr <std::atomic <bool>> done = std::make_shared <std::atomic <bool>> (false);

    std::chrono::time_point <std::chrono::high_resolution_clock> ctor, start, end, dtor;

private:
    static std::atomic <std::size_t> accumulated_idle;
    static std::atomic <std::size_t> accumulated_work;

    static std::atomic <int> ID_ctr;
};

std::ostream & operator << (std::ostream & os, ITask const & task);


#endif //CONCURRENT_ITASK_H

/* Copyright (C) 2021 Aaron Alef */
