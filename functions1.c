#include "main.h"

/* A function to print unsigned number to a character buffer */
/**
 * print_unsigned - Prints an unsigned number char buffer
 * @types:  Arguments list
 * @buffer: Buffer array to hand print output
 * @flags:  Active flags calculation
 * @width: Find width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int g = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[g--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[g--] = (number % 10) + '0';
		number /= 10;
	}

	g++;

	return (write_unsgnd(0, g, buffer, flags, width, precision, size));
}

/* function to print unsigned number in octal notation*/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types:  Arguments list
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Find width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int c = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_num = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[c--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[c--] = (number % 8) + '0';
		number /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[c--] = '0';

	c++;

	return (write_unsgnd(0, c, buffer, flags, width, precision, size));
}

/* functions that print unsigned numbers in hexadecimal notations*/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: Arguments list
 * @buffer: Buffer array to handle print as input
 * @flags:  Calculates active flags
 * @width: find width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/* functions to print unsigned number in upper hexadecimal notation*/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Arguments list
 * @buffer: Buffer array to handle print as input
 * @flags:  Calculates active flags
 * @width: Find width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of character printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/*functions to print hexadecimal number in upper or lower notation*/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper notation
 * @types: Arguments list
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print inputs
 * @flags:  Active flags are calculated
 * @flag_ch: Active flags are calculated
 * @width: find width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of character printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int b = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_num = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[b--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[b--] = map_to[number % 16];
		number /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[b--] = flag_ch;
		buffer[b--] = '0';
	}

	b++;

	return (write_unsgnd(0, b, buffer, flags, width, precision, size));
}

