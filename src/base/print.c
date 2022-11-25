#include "print.h"

void print(const char* time, const char* file, const char* func, int line, const char *f, ...) {
	int i = 0;
	va_list arg_ptr;

	va_start(arg_ptr, f);
	vsnprintf(buf, DPRINT_SIZE, f, arg_ptr);
    va_end(arg_ptr); 
    printf("\033[%d;%dm[%s]\033[0m %s %s:%04d %s\n", DEBUG_BACK_COLOR, DEBUG_FONT_COLOR, time, file, func, line, buf);
}