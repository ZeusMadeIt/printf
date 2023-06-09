#include "main.h"

int _printf(const char *format, ...)
{
	unsigned int written;
	va_list args;
	int long_flag;
	int short_flag;

	va_start(args, format);
	written = 0;
	long_flag = 0;
	short_flag = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			++format;

			if (*format == 'l')
			{
				long_flag = 1;
				++format;
			}
			else if (*format == 'h')
			{
				short_flag = 1;
				++format;
			}

			switch (*format)
			{
				case 'd':
				case 'i':
					{
						int value = (long_flag ? va_arg(args, long) : 
							(short_flag ? (short)va_arg(args, int) : va_arg(args, int)));
						written += (unsigned int) _print_integer(value, 10, 0);
						break;
					}

				case 'u':
				case 'o':
				case 'b':
				case 'x':
				case 'X':
					{
						int base = (*format == 'o') ? 8 : ((*format == 'x' || *format == 'X') ? 16 : ((*format == 'b') ? 2 : 10));
						int uppercase = (*format == 'X') ? 1 : 0;
						unsigned int value = (long_flag ? va_arg(args, unsigned long) : 
							(short_flag ? (unsigned short)va_arg(args, unsigned int) : va_arg(args, unsigned int)));
						written += (unsigned int) _print_unsigned(value, base, uppercase);
						break;
					}

				case 'c':
					{
						char c = (char) va_arg(args, int);
						written += (unsigned int) _putchar(c);
						break;
					}

				case '%':
					{
						written += (unsigned int) _putchar(37);
						break;
					}

				case 'p':
					{
						written += (unsigned int) _printf_pointer(args);
						break;
					}

				case 's':
					{
						char *str = va_arg(args, char *);
						if (str == NULL)
							str = "(null)";
						written += (unsigned int) _printstring(str);
						break;
					}

				case 'S':
					{
						written += (unsigned int) _print_exclusive_string(args);
						break;
					}

				case 'r':
					{
						written += (unsigned int) _printf_srev(args);
						break;
					}

				case 'R':
					{
						written += (unsigned int) _printf_rot13(args);
						break;
					}

				default:
					{
						write(1, format-1, 2);
						written += 2;
						break;
					}
			}
		}
		else
		{
			written += (unsigned int) _putchar(*format);
		}
		format++;
	}
	va_end(args);
	return (written);
}

