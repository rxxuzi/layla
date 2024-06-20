// colors.h
#ifndef COLORS_H
#define COLORS_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#define GLC_ERROR    "\x1b[31m"
#define GLC_SUCCESS  "\x1b[32m"
#define GLC_WARNING  "\x1b[33m"
#define GLC_INFO     "\x1b[34m"
#define GLC_TRACE    "\x1b[35m"
#define GLC_DEBUG    "\x1b[36m"
#define GLC_RESET    "\x1b[0m"

void c_err(const char *format, ...);
void c_error(const char *format, ...);
void c_dbg(const char *format, ...);
void c_debug(const char *format, ...);
void c_warn(const char *format, ...);
void c_warning(const char *format, ...);
void c_info(const char *format, ...);
void c_ok(const char *format, ...);
void c_trace(const char *file, const char *func, int line, const char *format, ...);

#ifdef __cplusplus
}
#endif
#endif // COLORS_H
