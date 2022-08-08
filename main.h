#ifndef HEADER
#define HEADER
#include <stdarg.h>

#define BUF_LENGTH 1024

int _printf(const char *format, ...);
void error_format(const char *format);
int no_conversion(char);
char *_flush(char *buffer);
char *grab_format(const char *s);
char *(*get_mstring_func(char))(char *, va_list vl);

int _strlen(const char *);
char *fill_buffer(char *buffer, const char *s, int count_c, int s_length);
void print_buffer(char *buffer, int length);

























#endif
