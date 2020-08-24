#ifndef _INCLUDE_MEM_IO_H_
#define _INCLUDE_MEM_IO_H_

#include "stdint.h"

#define SET_BIT(p,n)	( (p) |=  (1 << (n)) )
#define CLR_BIT(p,n)	( (p) &= ~(1 << (n)) )
#define memclr(p,n)		{					\
	for (uint32_t i = 0; i < n; i++)		\
		((uint8_t *)p)[i] = 0;				\
}

#endif 
