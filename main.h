#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int _printf(const char *format, ...);
typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_t;



#endif
