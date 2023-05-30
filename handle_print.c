#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @form: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @index: index.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates flags
 * @w: get width.
 * @p: presicion
 * @size: Size
 * Return: int ;
 */
int handle_print(const char *form, int *index, va_list list, char buffer[],
	int flags, int w, int p, int size)
{
	int i, length = 0, printed_c = -1;
	form_t form_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; form_types[i].form != '\0'; i++)
		if (form[*index] == form_types[i].form)
			return (form_types[i].f(list, buffer, flags, w, p, size));

	if (form_types[i].form == '\0')
	{
		if (form[*index] == '\0')
			return (-1);
		length += write(1, "%%", 1);
		if (form[*index - 1] == ' ')
			length += write(1, " ", 1);
		else if (w)
		{
			--(*index);
			while (form[*index] != ' ' && form[*index] != '%')
				--(*index);
			if (form[*index] == ' ')
				--(*index);
			return (1);
		}
		length += write(1, &form[*index], 1);
		return (length);
	}
	return (printed_c);
}
