#include "ITask.h"

std::atomic <int> ITask::ID_ctr = 0;

bool ITask::operator ! () const {
    return !done;
}
void ITask::await () const {
    while (! * this) std::this_thread::yield();
}
bool ITask::isDone() const {
    return done;
}
bool ITask::isRunning() const {
    return run && !done;
}
std::string ITask::toString() const {
    std::stringstream ss;
    ss << "Task #" << ID << ": " << ((done) ? "done" : (run) ? "running" : "idle");
    return ss.str();
}

std::ostream & operator << (std::ostream & os, ITask const & task) {
    return os << task.toString();
}

/* Copyright (C) 2020 Aaron Alef */
