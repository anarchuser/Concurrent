#ifndef CONCURRENT_HELPER_H
#define CONCURRENT_HELPER_H

#include <ostream>

template <typename T>
concept Streamable = requires (std::ostream & os, T const & t) { os << t; };

#endif //CONCURRENT_HELPER_H

/* Copyright (C) 2020 Aaron Alef */
