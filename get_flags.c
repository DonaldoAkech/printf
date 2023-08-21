#include "main.h"

/**
 * get_flags - Active flags calculation
 * @format: Formatted string to print arguments
 * @i:  Parameter is taken.
 * Return: Flags
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int d, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
	for (d = 0; FLAGS_CH[d] != '\0'; d++)
			if (format[curr_i] == FLAGS_CH[d])
			{
				flags |= FLAGS_ARR[d];
				break;
			}

		if (FLAGS_CH[d] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}

