#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "main.h"

/**
 * _printf - prints
 * return: the count
 */

int _printf(const char *format, ...)
{
	char index;
	unsigned int i;
	int count = 0;
	char *s;

	va_list arg;
	va_start(arg, format);

	for (index = *format; index != 0; index++)
	{
		while (index != '%')
		{
			_putchar(index);
			index++;
		}
		index++;
	}

	switch(index)
	{
		case 'c' : i = va_arg(arg, int);
		_putchar(i);
		count++;
		break;

		case 's' : s = va_arg(arg, char *);
		puts(s);
		count++;
		break;
	}

	va_end(arg);
	
	return count;

}
