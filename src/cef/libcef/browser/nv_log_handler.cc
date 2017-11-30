// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#include "include/cef_nv_log_handler.h"

unsigned int gLogLevel = 0;

namespace cef {

CefLogHandler* g_handler = NULL;

void setLogHandler(CefLogHandler* handler)
{
  g_handler = handler;

  // Also update the log level in the process:
  char* buf;
  buf = getenv("NV_CEF_LOG_LEVEL");
  gLogLevel = buf ? atoi(buf) : 0;
}

void handleLogMessage(unsigned int level, const std::string& msg)
{
  // Check if the level is acceptable:
  if(level > gLogLevel) {
    return; // we do not output this message.
  }

  if(g_handler) {
    g_handler->log(msg);
  }
}

}