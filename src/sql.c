#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <varags.h>

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
