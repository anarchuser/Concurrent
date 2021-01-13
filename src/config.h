#ifndef CONCURRENT_CONFIG_H
#define CONCURRENT_CONFIG_H

// Minimum LOG level. 0 = Everything, 1 = Ignore LOG (INFO), ...
#define GOOGLE_STRIP_LOG 0
#include <glog/logging.h>

#include <string>
std::string const STR = std::string();

#ifdef ERRORS_AS_WARNINGS
#define THROW(error) {              \
    LOG (WARNING) << error.what();  \
    throw error;                    \
}; true
#else
#define THROW(error) {              \
    LOG (ERROR) << error.what();    \
    throw error;                    \
}; true
#endif

#define ITERATIONS 20
#define MAX_FIB 50

#endif //CONCURRENT_CONFIG_H

/* Copyright (C) 2020 Aaron Alef */
