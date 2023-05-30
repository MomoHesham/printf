#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @index: index.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *index, va_list list)
{
	int curr_index = *index + 1;
	int prec = -1;

	if (format[curr_index] != '.')
		return (prec);

	prec = 0;

	for (curr_index += 1; format[curr_index] != '\0'; curr_index++)
	{
		if (is_digit(format[curr_index]))
		{
			prec *= 10;
			prec += format[curr_index] - '0';
		}
		else if (format[curr_index] == '*')
		{
			curr_index++;
			prec = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*index = curr_index - 1;

	return (prec);
}
