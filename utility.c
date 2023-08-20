#include "main.h"

/**
 * is_printable - Determine if a character is printable
 * @c: The character to check.
 *
 * Return: 1 if 'c' is printable, 0 otherwise.
 */

int is_printable(char c)
{
	/* Check if the given character is printable */
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Add ASCII in hexadecimal format to buffer
 * @ascii_code: ASCII code to add.
 * @buffer: Character array to append to.
 * @j: Starting index for appending.
 *
 * Return: Always returns 3.
 */
int append_hexa_code(char ascii_code, char buffer[], int j)
{ /* Append ASCII in hexadecimal format to the buffer at the given index */
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[j++] = '\\';
	buffer[j++] = 'x';

	buffer[j++] = map_to[ascii_code / 16];
	buffer[j] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Check if a character is a digit
 * @c: The character to evaluate.
 *
 * Return: 1 if 'c' is a digit, 0 otherwise.
 */

int is_digit(char c)
{ /* Checks if a given character is a numeric digit */
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Convert a number to the specified size
 * @num: Number to be converted.
 * @size: Size specifier for the conversion.
 *
 * Return: Converted value of 'num'.
 */

long int convert_size_number(long int num, int size)
{ /* Convert a number to the specified size using casting */
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Convert a number to the specified size
 * @num: Number to be converted
 * @size: Size specifier for the conversion
 *
 * Return: Converted value of 'num'
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{ /* Convert an unsigned number to the specified size using casting */
	if (size == S_LONG)
		return (num);
	else if (size 
			
			
			
			
			
			
			HORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
