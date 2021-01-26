#ifndef CONCURRENT_ITASK_H
#define CONCURRENT_ITASK_H

#include <functional>
#include <sstream>
#include <string>
#include <thread>

struct ITask {
public:
    const int ID = ID_ctr++;

    virtual void operator () () = 0;
    [[nodiscard]] virtual bool operator ! () const;
    virtual void await () const;
    [[nodiscard]] virtual bool isDone () const;
    [[nodiscard]] virtual bool isRunning () const;

    [[nodiscard]] virtual std::string toString () const;

protected:
    volatile bool run = false;
    volatile bool done = false;

private:
    static std::atomic <int> ID_ctr;
};

std::ostream & operator << (std::ostream & os, ITask const & task);


#endif //CONCURRENT_ITASK_H

/* Copyright (C) 2020 Aaron Alef */
