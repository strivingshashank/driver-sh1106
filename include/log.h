#ifndef LOG_H
#define LOG_H

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#define COLOR_RESET "\033[0m"
#define COLOR_RED   "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE  "\033[34m"
#define COLOR_CYAN  "\033[36m"

#define SET_SERIAL_COLOUR(COLOUR) printf(COLOUR);

static inline void _log(const char *colour, const char *level,const char *format, va_list args) {
        assert(format);

        printf("%s%s >> ", colour, level);
        vprintf(format, args);
        printf("%s\n", COLOR_RESET);
}

static inline void log_debug(const char *format, ...) {
        va_list args;
        va_start(args, format);
        _log(COLOR_YELLOW, "DEBUG", format, args);
}

static inline void log_info(const char *format, ...) {
        va_list args;
        va_start(args, format);
        _log(COLOR_GREEN, "INFO", format, args);
}

static inline void log_error(const char *format, ...) {
        va_list args;
        va_start(args, format);
        _log(COLOR_RED, "ERROR", format, args);
}

#endif
