// Copyright (c) 2017 Emmanuel ROCHE

#ifndef CEF_NV_EXPORTS_H_
#define CEF_NV_EXPORTS_H_
#pragma once

#include "include/internal/cef_export.h"
#include "include/cef_nv_log_handler.h"

#ifdef __cplusplus
extern "C" {
#endif

///
// This function should be called on the main application thread to assign
// a log handler to the CEF module (used for investigations)
///
CEF_EXPORT void cef_set_log_handler(cef::CefLogHandler* handler);

#ifdef __cplusplus
}
#endif


#endif
