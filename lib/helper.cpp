#include "helper.h"

std::ostream & operator << (std::ostream & os, std::chrono::time_point <std::chrono::high_resolution_clock> const & time) {
    auto time_t = std::chrono::high_resolution_clock::to_time_t (time);
    return os << std::put_time (std::localtime (& time_t), "%T");
}


/* Copyright (C) 2020 Aaron Alef */
