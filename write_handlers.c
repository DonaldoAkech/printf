#include "main.h"

/* functions used to handle printed strings*/
/**
 * handle_write_char - Prints character string to standard output
 * @c: character types.
 * @buffer: Buffer array to handle print
 * @flags:  Active flags are calculated
 * @width: Find width.
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int b = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';
	buffer[b++] = c;
	buffer[b] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (b = 0; b < width - 1; b++)
			buffer[BUFF_SIZE - b - 2] = padd;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - b - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - b - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/* functions used to handle numbers to standard ouput*/
/**
 * write_number - Prints a character string to standard output
 * @is_negative: Arguments lista
 * @ind: character types.
 * @buffer: Buffer array to handle print
 * @flags:  Active flags are calculated
 * @width: find width.
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Number of character printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';
	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index that the number starts on the buffer
 * @buffer: Buffer arrays
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading character
 * @extra_c: Extra character
 * Return: Number of printed characters..
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int g, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (g = 1; g < width - length + 1; g++)
			buffer[g] = padd;
		buffer[g] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], g - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], g - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], g - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
	buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index that the number starts in the buffer
 * @buffer: Array of character
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of written charsacter
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, g = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (width > length)
	{
		for (g = 0; g < width - length; g++)
			buffer[g] = padd;

		buffer[g] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], g));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], g) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory pointer address
 * @buffer: Arrays of character
 * @ind: Index that the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Character depicting the padding
 * @extra_c: Character depicting extra character
 * @padd_start: Index at which padding should start
 * Return: Number of written characters.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int g;

	if (width > length)
	{
		for (g = 3; g < width - length + 3; g++)
			buffer[g] = padd;
		buffer[g] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], g - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], g - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], g - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

