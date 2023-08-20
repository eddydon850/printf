#include "main.h"

/***************** WRITE HANDLE ******************/
/**
 * handle_write_char - Prints a character
 * @c: The character to be printed.
 * @buffer: Buffer array to handle printing.
 * @flags: Flags that control formatting.
 * @width: Minimum width of the printed output.
 * @precision: Maximum number of characters to be printed.
 * @size: Size of the printed character.
 *
 * Return: Number of charaacter to be printed.
 */

int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{ /* Left side holds the character, right side for padding. */
	int j = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[j++] = c;
	buffer[j] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (j = 0; j < width - 1; j++)
			buffer[BUFF_SIZE - j - 2] = padd;

		if (flags % F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - j - 1], width - 1));
		else
			return(write(1, &buffer[BUFF_SIZE - j - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/*********************** WRITE NUMBER **********************/
/**
 * write_number - Print a number
 * @is_negative: Indicate if the number is negative.
 * @ind: Index for current position in buffer.
 * @buffer: Buffer array to handle printing.
 * @flags: Calculation of active flags.
 * @width: Minimum width for formatting.
 * @precision: The precision specifier.
 * @size: The size specifier.
 *
 *
 * Return: Number of characters to be printed
 */
int write_number(int is_negative, int ind, char buffer[], int flags,
		int width, int precision, int size)
{
	/* Print a formatted number */
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

	return (write_num(ind, buffer, flags, width, precision, length,
				padd, extra_ch));
}

/**
 * write_num - Write a number using buffer
 * @ind: Starting index in the buffer
 * @buffer: Buffer to write into.
 * @flags: Formatting flags.
 * @width: Minimum qidth for formatting.
 * @prec: The precision specifier
 * @length: The length of the number
 * @padd: The padding character.
 * @extra_c: An additional character.
 *
 * Return: Number of characters printed.
 */
int write_num(int ind, char buffer[], int flags, int width,
		int prec, int length, char padd, char extra_c)
{ /* Write a formatted number using a buffer */
	int j, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (j = 1; j < width - length + 1; j++)
			buffer[j] = padd;
		buffer[j] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], j - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], j - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], j - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Produce output for an unsigned number
 * @is_negative: Sign indicator for the number (negative or not)
 * @ind: Index pointing to the beginning of the number in the buffer
 * @buffer: Character array for storage
 * @flags: Specifications for formatting
 * @width: Minimum width for formatting consideration
 * @precision: Maximum digits allowed for precision
 * @size: Magnitude specifier
 *
 * Return: Count of character generated in the output.
 */
int write_unsgnd(int is_negative, int ind, char buffer[], int flags,
		int width, int precision, int size)
{ /* Output an unsigned number using given formatting */

	int length = BUFF_SIZE - ind - 1, j = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

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
		for (j = 0; j < width - length; j++)
			buffer[j] = padd;

		buffer[j] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], j));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Generate output for a memory address
 * @buffer: Character array for storage
 * @ind: Starting index of the address in the buffer
 * @length: Length of the address
 * @width: Width specification
 * @flags: Formatting flags
 * @padd: Character for padding
 * @extra_c: Extra character
 * @padd_start: Index to begin padding
 *
 * Return: Count of characters generated in the output.
 */
int write_pointer(char buffer[], int ind, int length, int width, int flags,
		char padd, char extra_c, int padd_start)
{
	/* Output a formatted memory address using provided parameters */
	int j;

	if (width > length)
	{
		for (j = 3; j < width - length + 3; j++)
			buffer[j] = padd;
		buffer[j] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], j - 3));
		}
		else if (!(flags & F_MINUS) & padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], j - 3) +
					write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], j - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
