#include "main.h"

/**
 * get_size - Calculate size for casting the argument
 * @format: Format string containing the argument specifier
 * @j: Argument to be printed
 *
 * Return: Size for casting.
 */

int get_size(const char *format, int *j)
{ /* Calculate size for casting argument based on format specifier */
	int curr_i = *j + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = S_LONG;
	else if (format[curr_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*j = curr_i - 1;
	else
		*j = curr_i;

	return (size);
}
