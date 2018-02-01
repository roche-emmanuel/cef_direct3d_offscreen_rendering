// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#include "gpu/command_buffer/service/nv_logger.h"
#include "base/process/process.h"
#include "base/threading/platform_thread.h"
#include "base/time/time.h"
#include <fstream>

/** Helper class used to write to a file */
class nvLogger
{
public:
  nvLogger(): _file("cef_nv.log"), _initialized(false) {}

  ~nvLogger() {
    if(_initialized) {
      log("Destroying nvLogger.");
      _stream.close();
    }
  }

  void init();

  void log(const std::string& msg);

private:
  std::string _file;
  bool _initialized;
  std::ofstream _stream;
};

void nvLogger::init() {
  // Init the log file here:
	if(_stream.is_open())
		_stream.close(); // close previous stream if any.
	
  _stream.open(_file.c_str(), std::ofstream::out);

  _initialized = true;
  log("nvLogger initialized.");
}

void nvLogger::log(const std::string& msg)
{
  if(!_initialized) {
    init();
  }

  // Log the message here:
  auto pid = base::Process::Current().Pid();
  auto tid = base::PlatformThread::CurrentId();

  _stream << base::Time::Now() << " [" << pid << "]{" << tid << "}: " << msg << std::endl;
  _stream.flush();
}

// Global instance of the logger:
nvLogger gLogger;

namespace nv {

void nvLOG(const std::string& msg)
{
  gLogger.log(msg);
}

}