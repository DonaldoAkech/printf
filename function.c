#include "main.h"

/* function to print character */

/**
 * print_char - character to prints
 * @types: arguments lists
 * @buffer: Buffer array to handle print
 * @flags:  it calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char d = va_arg(types, int);

	return (handle_write_char(d, buffer, flags, width, precision, size));
}
/* function to print a string */
/**
 * print_string - prints a string
 * @types: Arguments lists
 * @buffer: Buffer array to handle print
 * @flags:  active flags are calculated
 * @width: find width.
 * @precision: for Precision specification
 * @size: For size specifier
 * Return: Number of characters printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, f;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (f = width - len; f > 0; f--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (f = width - len; f > 0; f--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}
/*function to Print percentage sign */
/**
 * print_percent - Prints a percent sign
 * @types: Arguments list
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Find width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/* Print integers function */
/**
 * print_int - Print int
 * @types: Arguments list
 * @buffer: Buffer array to handle print
 * @flags:  Active flags are calculted
 * @width: Find width.
 * @precision: Precision specification
 * @size: For Size specifier
 * Return: Number of character printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int h = BUFF_SIZE - 2;
	int is_negative = 0;
	long int g = va_arg(types, long int);
	unsigned long int num;

	g = convert_size_number(g, size);

	if (g == 0)
		buffer[h--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)g;

	if (g < 0)
	{
		num = (unsigned long int)((-1) * g);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[h--] = (num % 10) + '0';
		num /= 10;
	}

	h++;

	return (write_number(is_negative, h, buffer, flags, width, precision, size));
}

/* fumction to print a binary number */
/**
 * print_binary - Prints an unsigned binary number
 * @types: Arguments list
 * @buffer: Buffer to handle print output.
 * @flags:  Calculates active flags
 * @width: find width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: char numbers printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int k, l, j, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	k = va_arg(types, unsigned int);
	l = 2147483648; /* (2 ^ 31) */
	a[0] = k / l;
	for (j = 1; j < 32; j++)
	{
		l /= 2;
		a[j] = (k / l) % 2;
	}
	for (j = 0, sum = 0, count = 0; j < 32; j++)
	{
		sum += a[j];
		if (sum || j == 31)
		{
			char z = '0' + a[j];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

