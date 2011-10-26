#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdargs.h>

#include "sql.h"

int exec_on_database(sqlite *db, const char *fmt, ...);

int create_database(sqlite *db)
{
	return 0;
}

int update_database(sqlite *db)
{
	return 0;
}

int exec_on_database(sqlite *db, const char *fmt, ...)
{
	char buffer[BUFFER_SIZE];

	va_list args;
	va_start(args, fmt);
	sprintf(buffer, fmt, args);
	va_end(args);

	return 0;
}
