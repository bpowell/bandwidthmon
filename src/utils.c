#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdargs.h>

void error(const char *fmt, ...)
{
	va_list args;
	va_start(fmt, args);
	fprintf(stderr, fmt, args);
	va_end(args);

	exit(1);
}
