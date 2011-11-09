#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#include "sql.h"
#include "utils.h"

void exec_on_database(sqlite3 *db, const char *fmt, ...);


int is_database_created(const char *filename)
{
	return access(filename, F_OK);
}

void open_database()
{
	int rc = sqlite3_open(db_filename, &sql_db);
	if(rc)
	{
		error("Error opening database.\n");
	}
}

void create_database()
{
	if(!is_database_created(db_filename))
	{	
		printf("created a;ready.\n");
		open_database();
		return;
	}

	open_database();
	exec_on_database(sql_db, "%s", SQL_CREATE_HOURS);
	exec_on_database(sql_db, "%s", SQL_CREATE_DAYS);
	exec_on_database(sql_db, "%s", SQL_CREATE_WEEKS);
	exec_on_database(sql_db, "%s", SQL_CREATE_MONTHS);
	exec_on_database(sql_db, "%s", SQL_CREATE_YEARS);
}

void update_database(struct bandwidth_info bw)
{
	fprintf(stdout, "updating database");
	fflush(stdout);
}

void exec_on_database(sqlite3 *db, const char *fmt, ...)
{
	char buffer[BUFFER_SIZE];
	char *ebuf = 0;

	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);

	int rc = sqlite3_exec(db, buffer, NULL, 0, &ebuf);
	if(rc)
	{
		error("Error:\n%s\n", ebuf);
	}

}
