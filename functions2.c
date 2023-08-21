#include "main.h"

/* functions that prints pointers*/
/**
 * print_pointer - It prints the value of a pointer variable
 * @types:  Arguments list
 * @buffer: Buffer array to handle print
 * @flags:  Active flags are calculated
 * @width: find width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, len = 2, padd_start = 1; /* len=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', len++;
	else if (flags & F_SPACE)
		extra_c = ' ', len++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, len,
		width, flags, padd, extra_c, padd_start));
}

/* functions to print non printable character */
/**
 * print_non_printable - Prints ASCII codes in hexadecimal
 *  of non printable character
 * @types: Arguments lists
 * @buffer: Buffer array to handle print
 * @flags:  Active flags are calculated
 * @width: find width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int p = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[p] != '\0')
	{
		if (is_printable(str[p]))
			buffer[p + offset] = str[p];
		else
			offset += append_hexa_code(str[p], buffer, p + offset);

		p++;
	}

	buffer[p + offset] = '\0';

	return (write(1, buffer, p + offset));
}

/* functions to print string in a reverse order */
/**
 * print_reverse - prints rev strings
 * @types: Arguments lista
 * @buffer: Buffer array to handle print
 * @flags: Active flags calculations
 * @width: find width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of character printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int c, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (c = 0; str[c]; c++)
		;

	for (c = c - 1; c >= 0; c--)
	{
		char z = str[c];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/*function that prints a string ROT13 encoding */
/**
 * print_rot13string - Print a string in rot13 encoding.
 * @types: Arguments lista
 * @buffer: Buffer array to handle print input.
 * @flags:  Calculates active flags
 * @width: find width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of character printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char z;
	char *str;
	unsigned int a, b;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (a = 0; str[a]; a++)
	{
		for (b = 0; in[b]; b++)
		{
			if (in[b] == str[a])
			{
				z = out[b];
				write(1, &z, 1);
				count++;
				break;
			}
		}
		if (!in[b])
		{
			z = str[a];
			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

