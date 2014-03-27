#ifndef _UTILS_H_
#define _UTILS_H_

#include <time.h>

extern void error(const char* fmt, ...) __attribute__((noreturn));
extern struct tm *get_time();

#endif
