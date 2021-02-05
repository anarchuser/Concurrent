#include "ITask.h"

std::atomic <int> ITask::ID_ctr = 0;

std::atomic <std::size_t> ITask::accumulated_idle = 0;
std::atomic <std::size_t> ITask::accumulated_work = 0;

ITask::~ITask() {
//    if (end <= start) return;
    auto dtor = std::chrono::high_resolution_clock::now();
    accumulated_idle += (start -  ctor).count();
    accumulated_work += (end   - start).count();
    STD_OSTREAM <<
                "Task ID "   << (int) ID <<
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

bool ITask::operator ! () const {
    return !isDone();
}
bool ITask::isDone() const {
    return * done;
}
bool ITask::isRunning() const {
    return run && !isDone();
}
std::string ITask::toString() const {
    std::stringstream ss;
    ss << "Task #" << ID << ": " << (isDone() ? "done" : (run) ? "running" : "idle");
    return ss.str();
}

std::ostream & operator << (std::ostream & os, ITask const & task) {
    return os << task.toString();
}

/* Copyright (C) 2021 Aaron Alef */