#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints an unsigned number
 * @list: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates flags
 * @w: get width
 * @p: presicion
 * @size: Size
 * Return: Number of chars printed.
 */
int print_unsigned(va_list list, char buffer[],
	int flags, int w, int p, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int n = va_arg(list, unsigned long int);

	n = convert_size_unsgnd(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[i--] = (n % 10) + '0';
		n /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, w, p, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates flags
 * @w: get w
 * @p: p
 * @size: Size
 * Return: Number of chars printed
 */
int print_octal(va_list list, char buffer[],
	int flags, int w, int p, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int n = va_arg(list, unsigned long int);
	unsigned long int init_n = n;

	UNUSED(w);

	n = convert_size_unsgnd(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[i--] = (n % 8) + '0';
		n /= 8;
	}

	if (flags & F_HASH && init_n != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, w, p, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates flags
 * @w: get w
 * @p: p
 * @size: Size
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list list, char buffer[],
	int flags, int w, int p, int size)
{
	return (print_hexa(list, "0123456789abcdef", buffer,
		flags, 'x', w, p, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates flags
 * @w: get w
 * @p: p
 * @size: Size
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list list, char buffer[],
	int flags, int w, int p, int size)
{
	return (print_hexa(list, "0123456789ABCDEF", buffer,
		flags, 'X', w, p, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @list: List of arguments
 * @mapping: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates  flags
 * @flag_c: Calculates  flags
 * @w: get w
 * @p: p
 * @size: Size
 * Return: Number of chars printed
 */
int print_hexa(va_list list, char mapping[], char buffer[],
	int flags, char flag_c, int w, int p, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int n = va_arg(list, unsigned long int);
	unsigned long int init_n = n;

	UNUSED(w);

	n = convert_size_unsgnd(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[i--] = mapping[n % 16];
		n /= 16;
	}

	if (flags & F_HASH && init_n != 0)
	{
		buffer[i--] = flag_c;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, w, p, size));
}
