#include "Executor.h"

// public //
Executor::Executor () {
    for (std::size_t worker = workers.size(); worker < AVAILABLE_THREADS; ++worker) {
        workers.template emplace_back (std::make_unique <Worker <ITask>>());
    }
}

Executor::~Executor () {
    await();
}

void Executor::await () const {
    while (!empty()) std::this_thread::yield();
}

bool Executor::operator ! () const {
    return empty();
}

bool Executor::empty () const {
    for (auto const & worker : workers)
        if (!worker->empty())
            return false;
    return true;
}

std::size_t Executor::size () const {
    std::size_t sum = 0;
    for (auto const & worker : workers)
        sum += worker->size();
    return sum;
}

std::string Executor::toString () const {
    std::stringstream ss;
    ss << "Executor - tasks left: " << size();
    return ss.str();
}


// private //
std::vector <std::unique_ptr <Worker <ITask>>> Executor::workers = std::vector <std::unique_ptr <Worker <ITask>>>();

Worker <ITask> & Executor::next () {
    std::size_t min = -1;
    std::size_t min_idx;
    for (std::size_t idx = 0; idx < AVAILABLE_THREADS; ++idx) {
        if (workers [idx]->size() < min) {
            min = workers [idx]->size();
            min_idx = idx;
        }
    }
    return * workers [min_idx];
}

/* Copyright (C) 2020 Aaron Alef */