/*
 * mini-scanf - Minimal scanf() implementation for embedded projects. 
 * Copyright (c) 2023 Aleksej Muratov
 */

#define LENSCANS 10
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

static inline int isspace(const int c)
{
	switch (c)
	{ /* in the "C" locale: */
		case ' ': /* space */
		case '\f': /* form feed */
		case '\n': /* new-line */
		case '\r': /* carriage return */
		case '\t': /* horizontal tab */
		case '\v': /* vertical tab */
			return 1;
		default:
			return 0;
	}
}

// std
static inline int isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// parodies the standard
#define NEXTCHAR (PointBuf++)
#define CURCHAR (buff[PointBuf])
int sscanf(const char* buff, char* format, ...)
{
	int count = 0;

	int PointBuf = 0;

	int PointFt = 0;

	va_list ap;
	va_start(ap, format);
	while (format && format[PointFt]) // Read format
	{
		if (format[PointFt] == '%')
		{
			PointFt++;
			// for %*
			bool save = true;
			if (format[PointFt] == '*')
			{
				save = false;
				PointFt++;
			}
			// for %1234567890
			unsigned len = 0;
			bool lenEn = false;
			while (isdigit(format[PointFt]))
			{
				lenEn = true;
				len *= 10;
				len += (format[PointFt] - '0');
				PointFt++;
			}
			// for %[]
			char stop[LENSCANS];
			unsigned stopN = 0;
			if (format[PointFt] == '[')
			{
				while (format[PointFt] != ']')
				{
					if (format[PointFt] != '[')
					{
						stop[stopN] = format[PointFt];
						stopN++;
					}
					PointFt++;
				}
			}
			// %?
			switch (format[PointFt])
			{
				case 'c':
					while (isspace(CURCHAR)) // ignore isspace (std)
						NEXTCHAR; //
					if (save)
						*(char*)va_arg(ap, char*) = CURCHAR;
					NEXTCHAR;
					//if (save) // ignore %* (std)
						count++;
					break;
				case 'u':
				case 'd':
					int sign = 1;
					while (!isdigit(CURCHAR))
					{
						if (CURCHAR == '+' || CURCHAR == '-')
							if (CURCHAR == '-')
								//if(format[PointFt] != 'u') // ignore sign (no std)
									sign = -1;
						NEXTCHAR;
					}
					long value = 0;
					while(isdigit(CURCHAR) && (lenEn != true || len > 0))
					{
						value *= 10;
						value += (int)(CURCHAR - '0');
						NEXTCHAR;
						len--;
					}

					if (save)
						*(int*)va_arg(ap, int*) = value * sign;
					//if (save) // ignore %* (std)
						count++;
					break;
				case ']':
				case 's':
					char* t = save ? va_arg(ap, char*) : NULL;

					while (isspace(CURCHAR)) // ignor isspace (std)
						NEXTCHAR; //

					while (true)
					{
						bool con = false;
						if (stopN != 0)
						{
							bool invert = (stop[0] == '^');
							con = !invert;
							for (unsigned i = (invert ? 1 : 0); i < stopN; i++)
								if (stop[i] == CURCHAR)
								{
									con = invert;
									break;
								}

							if (con == true)
								break;
						}

						if (!isspace(CURCHAR) || (!con && stopN != 0) && (lenEn != true || len > 0))
						{
							if (save)
								*t = CURCHAR;
							NEXTCHAR;
							t++;
							len--;
						}
						else
							break;
					}
					// add \0
					{
						if (save)
							*t = '\0';
						t++;
					}
					//if (save) // ignore %* (std)
						count++;
					break;
			}
		}
		//else  // drop char in buff (no std)
		//	NEXTCHAR; //
		PointFt++;
	}
	va_end(ap);
	return count;
}
