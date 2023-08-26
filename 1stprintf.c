#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * _printf - Print formatted output to standard output.
 * @format: Format string.
 * @...: Additional arguments for placeholders.
 * Return: Number of printed characters.
 */

int _printf(const char *format, ...)
{
	va_list arg_start;

	ssize_t bit_wrote;

	int format_length;
	char output_buffer[1024];
	/* Buffer for storing formatted output */

	va_start(arg_start, format);

	format_length = vsnprintf(output_buffer,
			sizeof(output_buffer), format, arg_start);

	va_end(arg_start);

	if (format_length < 0)
	{
		perror("Error formatting output");
		return (-1);
	}

	bit_wrote = write(STDOUT_FILENO, output_buffer, format_length);

	if (bit_wrote == -1)
	{
		perror("Error writing to standard output");
		return (-1);
	}

	return (bit_wrote);
}
