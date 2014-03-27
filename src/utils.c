#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>

struct tm *get_time()
{
	time_t t;
	time(&t);
	return localtime(&t);
}

void error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, fmt, args);
	va_end(args);

	exit(1);
}
