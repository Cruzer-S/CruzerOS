#ifndef LIB_STDIO_H_
#define LIB_STDIO_H_

#include "stdarg.h"

#define NULL	(0)

typedef enum utoa_t
{
	utoa_dec = 10,
	utoa_hex = 16
} utoa_t;

uint32_t putstr(const char *);
uint32_t debug_printf(const char *, ...);
uint32_t vsprintf(char *, const char *, va_list );
uint32_t utoa(char *, uint32_t , utoa_t );

#endif
