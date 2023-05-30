#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates  flags.
 * @w: get width.
 * @p: precision
 * @size: Size
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int w, int p, int size)
{ /* char is stored at left and paddings at buffer's right */
	int ind = 0;
	char paddings = ' ';

	UNUSED(p);
	UNUSED(size);

	if (flags & F_ZERO)
		paddings = '0';

	buffer[ind++] = c;
	buffer[ind] = '\0';

	if (w > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (ind = 0; ind < w - 1; ind++)
			buffer[BUFF_SIZE - ind - 2] = paddings;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - ind - 1], w - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - ind - 1], w - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_neg: List of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates flags
 * @w: get w.
 * @p: p
 * @size: Size s
 *
 * Return: Number of chars printed.
 */
int write_number(int is_neg, int ind, char buffer[],
	int flags, int w, int p, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char paddings = ' ', plus_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddings = '0';
	if (is_neg)
		plus_ch = '-';
	else if (flags & F_PLUS)
		plus_ch = '+';
	else if (flags & F_SPACE)
		plus_ch = ' ';

	return (write_num(ind, buffer, flags, w, p,
		length, paddings, plus_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @w: w
 * @p: Precision
 * @length: Number length
 * @paddings: Pading char
 * @plus_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flags, int w, int p,
	int length, char paddings, char plus_c)
{
	int i, paddings_begins = 1;

	if (p == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && w == 0)
		return (0);
	if (p == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = paddings = ' ';
	if (p > 0 && p < length)
		paddings = ' ';
	while (p > length)
		buffer[--ind] = '0', length++;
	if (plus_c != 0)
		length++;
	if (w > length)
	{
		for (i = 1; i < w - length + 1; i++)
			buffer[i] = paddings;
		buffer[i] = '\0';
		if (flags & F_MINUS && paddings == ' ')
		{
			if (plus_c)
				buffer[--ind] = plus_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && paddings == ' ')
		{
			if (plus_c)
				buffer[--ind] = plus_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && paddings == '0')
		{
			if (plus_c)
				buffer[--paddings_begins] = plus_c;
			return (write(1, &buffer[paddings_begins], i - paddings_begins) +
				write(1, &buffer[ind], length - (1 - paddings_begins)));
		}
	}
	if (plus_c)
		buffer[--ind] = plus_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_neg: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags
 * @w: get width
 * @p: Precision
 * @size: Size
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_neg, int ind,
	char buffer[],
	int flags, int w, int p, int size)
{

	int length = BUFF_SIZE - ind - 1, i = 0;
	char paddings = ' ';

	UNUSED(is_neg);
	UNUSED(size);

	if (p == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (p > 0 && p < length)
		paddings = ' ';

	while (p > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddings = '0';

	if (w > length)
	{
		for (i = 0; i < w - length; i++)
			buffer[i] = paddings;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @w:get width
 * @flags: Flags
 * @paddings: Char representing the paddingsing
 * @plus_c: Char representing extra char
 * @paddings_begins: Index at which paddingsing should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int w, int flags, char paddings, char plus_c, int paddings_begins)
{
	int i;

	if (w > length)
	{
		for (i = 3; i < w - length + 3; i++)
			buffer[i] = paddings;
		buffer[i] = '\0';
		if (flags & F_MINUS && paddings == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (plus_c)
				buffer[--ind] = plus_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && paddings == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (plus_c)
				buffer[--ind] = plus_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && paddings == '0')
		{
			if (plus_c)
				buffer[--paddings_begins] = plus_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[paddings_begins], i - paddings_begins) +
				write(1, &buffer[ind], length - (1 - paddings_begins) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (plus_c)
		buffer[--ind] = plus_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

