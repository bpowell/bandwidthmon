#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

void error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, fmt, args);
	va_end(args);

	exit(1);
}
