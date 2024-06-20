#include "colors.h"
#include <stdio.h>
#include <time.h>

static void print_time(const char *color) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm);
    printf("%s [%s] %s", color, time_str, GLC_RESET);
}

static void print_formatted(const char *color, const char *format, va_list args) {
    printf("%s", color);
    vprintf(format, args);
    printf(GLC_RESET);
    printf("\n");
}

void c_out(const char *color, const char *format, va_list args) {
    print_time(color);
    print_formatted(color, format, args);
}

void c_err(const char *format, ...) {
    va_list args;
    va_start(args, format);
    print_formatted(GLC_ERROR, format, args);
    va_end(args);
}

void c_error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    c_out(GLC_ERROR, format, args);
    va_end(args);
}

void c_dbg(const char *format, ...) {
    va_list args;
    va_start(args, format);
    print_formatted(GLC_DEBUG , format, args);
    va_end(args);
}

void c_debug(const char *format, ...) {
    va_list args;
    va_start(args, format);
    c_out(GLC_DEBUG , format, args);
    va_end(args);
}

void c_warn(const char *format, ...) {
    va_list args;
    va_start(args, format);
    c_out(GLC_WARNING, format, args);
    va_end(args);
}

void c_waring(const char *format, ...) {
    va_list args;
    va_start(args, format);
    print_formatted(GLC_WARNING, format, args);
    va_end(args);
}

void c_info(const char *format, ...) {
    va_list args;
    va_start(args, format);
    print_formatted(GLC_INFO, format, args);
    va_end(args);
}

void c_ok(const char *format, ...) {
    va_list args;
    va_start(args, format);
    print_formatted(GLC_SUCCESS, format, args);
    va_end(args);
}

void c_trace(const char *file, const char *func, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char new_format[512];
    snprintf(new_format, sizeof(new_format), "[CODE %s:%d (%s)] %s", file, line, func, format);
    c_out(GLC_TRACE, new_format, args);
    va_end(args);
}



