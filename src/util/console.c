// colors.h
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "console.h"

static void set(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

static void del() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

HANDLE console;
COORD initialPosition;

void initCursorPosition() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(console, &csbi)) {
        initialPosition = csbi.dwCursorPosition;
    }
}

void resetCursorPosition() {
    SetConsoleCursorPosition(console, initialPosition);
}

void c_R(const char *format, ...) {
    set(FOREGROUND_RED | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
}

void c_G(const char *format, ...) {
    set(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
}

void c_B(const char *format, ...) {
    set(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
}

void c_C(const char *format, ...) {
    set(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
}

void c_Y(const char *format, ...) {
    set(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
}

void c_M(const char *format, ...) {
    set(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
}

void c_W(const char *format, ...) {
    set(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
}

void c_Beep(int frequency, int duration) {
    Beep(frequency, duration);
}

void c_err(const char *format, ...) {
    set(FOREGROUND_RED | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
    printf("\n");
    Beep(523, 20);
}

void c_warn(const char *format, ...) {
    set(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
    printf("\n");
    Beep(523, 20);
}

void c_info(const char *format, ...) {
    set(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
    printf("\n");
    Beep(523, 20);
}

void c_ok(const char *format, ...) {
    set(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
    printf("\n");
    Beep(523, 20);
}

void c_debug(const char *format, ...) {
    set(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    del();
    printf("\n");
    Beep(523, 20);
}