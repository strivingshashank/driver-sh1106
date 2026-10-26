#include "log.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_CYAN "\033[36m"

#define LEVEL_INFO 0
#define LEVEL_ERROR 1
#define LEVEL_DEBUG 2

void _log(int level, const char *format, va_list args) {
	assert(format);

	switch (level) {
	case LEVEL_INFO:
		printf("%s%s >> ", COLOR_GREEN, "INFO");
		vprintf(format, args);
		break;
	case LEVEL_ERROR:
		printf("%s%s >> ", COLOR_RED, "ERROR");
		vprintf(format, args);
		break;
	case LEVEL_DEBUG:
		printf("%s%s >> ", COLOR_YELLOW, "DEBUG");
		vprintf(format, args);
		break;
	default:
		// Should I add a special case here??
		break;
	}

	printf("%s\n", COLOR_RESET);
}

void log_debug(const char *format, ...) {
	va_list args;
	va_start(args, format);
	_log(LEVEL_DEBUG, format, args);
}

void log_info(const char *format, ...) {
	va_list args;
	va_start(args, format);
	_log(LEVEL_INFO, format, args);
}

void log_error(const char *format, ...) {
	va_list args;
	va_start(args, format);
	_log(LEVEL_ERROR, format, args);
}
