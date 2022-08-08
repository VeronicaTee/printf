#include "main.h"

unsigned char handle_flags(const char *flag, char *index);
unsigned char handle_length(const char *modifier, char *index);
int handle_width(va_list args, const char *modifier, char *index);
int handle_precision(va_list args, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/**
 * handle_flags - Matches flags with corresponding values.
 *
 * if true return a corresponding value.
 *         else - 0.
 */
unsigned char handle_flags(const char *flag, char *index)
{
	int i, j;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*index)++;
				if (ret == 0)
					ret = flags[j].value;
				else
					ret |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (ret);
}

/**
 * handle_length - Matches length modifiers with their corresponding value.
 *
 * if true return corresponding value.
 *         else - 0.
 */
unsigned char handle_length(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width - Matches a width modifier with its corresponding value.
 *
 * if true return value.
 *         else - 0.
 */
int handle_width(va_list args, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_precision - Matches a precision modifier with
 *                    its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential precision modifier.
 * @index: An index counter for the original format string.
 *
 * if true value.
 *         if null, zero, or negative return 0.
 *         else return -1.
 */
int handle_precision(va_list args, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
	     *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
	       (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_specifiers - Matches a conversion specifier with
 *                     a corresponding conversion function.
 *
 * if true return pointer to the function.
 *         else return NULL.
 */
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char)
{
	int i;
	converter_t converters[] = {
		{'d', convert_di},
		{'i', convert_di},
		{0, NULL}
	};

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}
