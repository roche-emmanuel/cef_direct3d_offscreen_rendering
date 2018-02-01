// Copyright (c) 2017 Emmanuel ROCHE

#ifndef CEF_NV_LOG_HANDLER_H_
#define CEF_NV_LOG_HANDLER_H_
#pragma once

#include <string>
#include <sstream>

namespace cef {

struct CefLogHandler {
 public:
  CefLogHandler() {};
  virtual ~CefLogHandler() {};

  // Log a message:
  virtual void log(const std::string& msg) = 0;
};

// Function used to set our log handler:
void setLogHandler(CefLogHandler* handler);

// Function used to actually log a message:
void handleLogMessage(const std::string& msg);

};

// Define a deBUG MESSAGE macro:
#define DEBUG_MSG(msg) { \
    std::ostringstream os; \
    os.precision(9); \
    os << std::fixed << msg; \
    cef::handleLogMessage(os.str()); \
}

#endif  // CEF_LIBCEF_LOG_HANDLER_H_
