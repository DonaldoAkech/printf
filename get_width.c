#include "main.h"

/**
 * get_width -  the width for printing is calculated.
 *by donaldo akech
 * @format: Formatted string to print the arguments.
 * @i: Arguments list to be printed.
 * @list: Arguments list.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int j;
	int width = 0;

	for (j = *i + 1; format[j] != '\0'; j++)
	{
		if (is_digit(format[j]))
		{
			width *= 10;
			width += format[j] - '0';
		}
		else if (format[j] == '*')
		{
			j++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = j - 1;

	return (width);
}

