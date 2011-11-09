#ifndef _BWM_SQL_H_
#define _BWM_SQL_H_

#define SQL_CREATE_HOURS	"create table hours(id INTEGER PRIMARY KEY, local_up INTEGER, local_down INTEGER, external_up INTEGER, external_down INTEGER);"
#define SQL_CREATE_DAYS		"create table days(id INTEGER PRIMARY KEY, local_up INTEGER, local_down INTEGER, external_up INTEGER, external_down INTEGER);"
#define SQL_CREATE_WEEKS	"create table weeks(id INTEGER PRIMARY KEY, local_up INTEGER, local_down INTEGER, external_up INTEGER, external_down INTEGER);"
#define SQL_CREATE_MONTHS	"create table months(id INTEGER PRIMARY KEY, local_up INTEGER, local_down INTEGER, external_up INTEGER, external_down INTEGER);"
#define SQL_CREATE_YEARS	"create table years(id INTEGER PRIMARY KEY, local_up INTEGER, local_down INTEGER, external_up INTEGER, external_down INTEGER);"

#define BUFFER_SIZE 	1000

#include <sqlite3.h>

#include "ipinfo.h"

sqlite3 *sql_db;
char *db_filename;

void create_database();
void update_database(struct bandwidth_info bw);

#endif
