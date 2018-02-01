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
void nvLOG(const std::string& msg);

};

// Define a DEBUG MESSAGE macro:
#define NV_LOG(msg) { \
    std::ostringstream os; \
    os.precision(9); \
    os << std::fixed << msg; \
    nv::nvLOG(os.str()); \
}

#endif  // CEF_LIBCEF_LOG_HANDLER_H_
