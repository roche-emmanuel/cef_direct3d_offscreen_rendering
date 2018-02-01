// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#include "include/cef_nv_log_handler.h"

namespace cef {

CefLogHandler* g_handler = NULL;

void setLogHandler(CefLogHandler* handler)
{
  g_handler = handler;
}

void handleLogMessage(const std::string& msg)
{
  if(g_handler) {
    g_handler->log(msg);
  }
}

}