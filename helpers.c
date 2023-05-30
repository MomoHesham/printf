#include "main.h"

/**
 * is_printable - Evaluates if a char is printable
 * @c: Char to be evaluated.
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer: Array of chars.
 * @ind: Index at which to start appending.
 * @ascii: ASSCI CODE.
 * Return: int
 */
int append_hexa_code(char ascii, char buffer[], int ind)
{
	char mapping[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii < 0)
		ascii *= -1;

	buffer[ind++] = '\\';
	buffer[ind++] = 'x';

	buffer[ind++] = mapping[ascii / 16];
	buffer[ind] = mapping[ascii % 16];

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit
 * @c: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @n: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of n
 */
long int convert_size_number(long int n, int size)
{
	if (size == S_LONG)
		return (n);
	else if (size == S_SHORT)
		return ((short)n);

	return ((int)n);
}

/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @n: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of n
 */
long int convert_size_unsgnd(unsigned long int n, int size)
{
	if (size == S_LONG)
		return (n);
	else if (size == S_SHORT)
		return ((unsigned short)n);

	return ((unsigned int)n);
}
