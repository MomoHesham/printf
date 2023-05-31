#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates flags
 * @w: get width
 * @p: presicion
 * @size: Size
 * Return: Number of chars printed.
 */
int print_pointer(va_list list, char buffer[],
	int flags, int w, int p, int size)
{
	char plus_c = 0, paddings = ' ';
	int ind = BUFF_SIZE - 2, length = 2, paddings_begins = 1;
	unsigned long num_address;
	char mapping[] = "0123456789abcdef";
	void *address = va_arg(list, void *);

	UNUSED(w);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(p);

	num_address = (unsigned long)address;

	while (num_address > 0)
	{
		buffer[ind--] = mapping[num_address % 16];
		num_address /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddings = '0';
	if (flags & F_PLUS)
		plus_c = '+', length++;
	else if (flags & F_SPACE)
		plus_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		w, flags, paddings, plus_c, paddings_begins));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates  flags
 * @w: get w
 * @p: p
 * @size: Size
 * Return: Number of chars printed
 */
int print_non_printable(va_list list, char buffer[],
	int flags, int w, int p, int size)
{
	int i = 0, off = 0;
	char *strn = va_arg(list, char *);

	UNUSED(flags);
	UNUSED(w);
	UNUSED(p);
	UNUSED(size);

	if (strn == NULL)
		return (write(1, "(null)", 6));

	while (strn[i] != '\0')
	{
		if (is_printable(strn[i]))
			buffer[i + off] = strn[i];
		else
			off += append_hexa_code(strn[i], buffer, i + off);

		i++;
	}

	buffer[i + off] = '\0';

	return (write(1, buffer, i + off));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse strning.
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates  flags
 * @w: get w
 * @p: p
 * @size: Size
 * Return: Numbers of chars printed
 */

int print_reverse(va_list list, char buffer[],
	int flags, int w, int p, int size)
{
	char *strn;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(w);
	UNUSED(size);

	strn = va_arg(list, char *);

	if (strn == NULL)
	{
		UNUSED(p);

		strn = ")Null(";
	}
	for (i = 0; strn[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = strn[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRnING IN ROT13 *************************/
/**
 * print_rot13string - Print a strning in rot13.
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates  flags
 * @w: get w
 * @p: p
 * @size: Size
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list list, char buffer[],
	int flags, int w, int p, int size)
{
	char x;
	char *strn;
	unsigned int i, j;
	int count = 0;
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	strn = va_arg(list, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(w);
	UNUSED(p);
	UNUSED(size);

	if (strn == NULL)
		strn = "(AHYY)";
	for (i = 0; strn[i]; i++)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == strn[i])
			{
				x = output[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!input[j])
		{
			x = strn[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
