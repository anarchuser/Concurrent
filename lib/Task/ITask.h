#ifndef CONCURRENT_ITASK_H
#define CONCURRENT_ITASK_H

#include <functional>
#include <sstream>
#include <string>
#include <thread>

struct ITask {
public:
    const int ID = ID_ctr++;

    [[nodiscard]] virtual bool operator ! () const;
    [[nodiscard]] virtual bool isDone () const;
    [[nodiscard]] virtual bool isRunning () const;

    [[nodiscard]] virtual std::string toString () const;

protected:
    std::atomic <bool> run = false;
    std::shared_ptr <std::atomic <bool>> done = std::make_shared <std::atomic <bool>> (false);

private:
    static std::atomic <int> ID_ctr;
};

std::ostream & operator << (std::ostream & os, ITask const & task);


#endif //CONCURRENT_ITASK_H

/* Copyright (C) 2021 Aaron Alef */
