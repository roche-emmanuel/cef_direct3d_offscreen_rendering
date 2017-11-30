// Copyright (c) 2017 Emmanuel ROCHE

#ifndef _NV_LOGGER_H_
#define _NV_LOGGER_H_
#pragma once

#include <string>
#include <sstream>

namespace nv {

/**
Helper logging function used to log debug outputs to a file.
*/
void nvLOG(unsigned int level, const std::string& msg);

};

// Define a DEBUG MESSAGE macro:
#define NV_LOG(msg) { \
    std::ostringstream os; \
    os.precision(9); \
    os << std::fixed << msg; \
    nv::nvLOG(1, os.str()); \
}

#define NV_LOG2(msg) { \
    std::ostringstream os; \
    os.precision(9); \
    os << std::fixed << msg; \
    nv::nvLOG(2, os.str()); \
}

#define NV_LOG3(msg) { \
    std::ostringstream os; \
    os.precision(9); \
    os << std::fixed << msg; \
    nv::nvLOG(3, os.str()); \
}

#endif  // CEF_LIBCEF_LOG_HANDLER_H_
