#ifndef STRING_H
#define STRING_H

#include "types.h"

void	*memcpy		(void *dest, const void *src, uint32_t count);
void	memset		(void *dest, uint8_t value, uint32_t count);
void	memsetw		(void *dest, uint16_t value, uint32_t count);
void	*memmove	(void *dest, const void *src, size_t len);

void	strcpy		(char *d, const char *s);
int		strlen		(const char *s);

#endif
