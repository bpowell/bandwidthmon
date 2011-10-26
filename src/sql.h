#ifndef _BWM_SQL_H_
#define _BWM_SQL_H_

#define SQL_CREATE_HOURS	"create table hours(id INTEGER PRIMARY KEY, local_up INTEGER, local_down INTEGER, external_up INTEGER, external_down INTEGER);"
#define SQL_CREATE_DAYS		"create table days(id INTEGER PRIMARY KEY, local_up INTEGER, local_down INTEGER, external_up INTEGER, external_down INTEGER);"
#define SQL_CREATE_WEEKS	"create table weeks(id INTEGER PRIMARY KEY, local_up INTEGER, local_down INTEGER, external_up INTEGER, external_down INTEGER);"
#define SQL_CREATE_MONTHS	"create table months(id INTEGER PRIMARY KEY, local_up INTEGER, local_down INTEGER, external_up INTEGER, external_down INTEGER);"
#define SQL_CREATE_YEARS	"create table years(id INTEGER PRIMARY KEY, local_up INTEGER, local_down INTEGER, external_up INTEGER, external_down INTEGER);"

#ifdef IN_MEMORY_DB
#define DATABASE ":memory:"
#else
#define DATABASE "bandwidthMon.db"
#endif 

#include <sqlite3.h>

extern int create_database(sqlite *db);
extern int update_database(sqlite *db);

#endif
