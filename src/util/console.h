// console.h
#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <windows.h>

void c_R(const char *format, ...);
void c_Y(const char *format, ...);
void c_G(const char *format, ...);
void c_B(const char *format, ...);
void c_M(const char *format, ...);
void c_C(const char *format, ...);
void c_W(const char *format, ...);

extern HANDLE console;
extern COORD initialPosition;

void initCursorPosition(void);
void resetCursorPosition(void);

void c_Beep(int frequency, int duration);

void c_err(const char *format, ...);
void c_warn(const char *format, ...);
void c_info(const char *format, ...);
void c_debug(const char *format, ...);
void c_ok(const char *format, ...);

#ifdef __cplusplus
}

#endif
#endif // CONSOLE_H
