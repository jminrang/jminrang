#include "string.h"

void *memcpy(void *dest, const void *src, uint32_t count) {
	const uint8_t *pSource = (const uint8_t *) src;
	uint8_t *pDest = (uint8_t *) dest;
	
	for (; count; --count) *pDest++ = *pSource++;
	return dest;
}

void memset(void *dest, uint8_t value, uint32_t count) {
	uint8_t *pDest = (uint8_t *) dest;
	for (; count; --count) *pDest++ = value;
}

void memsetw(void *dest, uint16_t value, uint32_t count) {
	uint16_t *pDest = (uint16_t *) dest;
	for (; count; --count) *pDest++ = value;
}

void *memmove(void *dest, const void *src, size_t len)
{
         size_t i;
 
         if ((uintptr_t)dest < (uintptr_t)src)
                 return memcpy(dest, src, len);
 
         if ((uintptr_t)dest % sizeof(long) == 0 &&
             (uintptr_t)src % sizeof(long) == 0 &&
             len % sizeof(long) == 0) {
 
                 long *d = dest;
                 const long *s = src;
 
                 for (i=len/sizeof(long); i>0; i--) 
                         d[i-1] = s[i-1];
         } else {
                 char *d = dest;
                 const char *s = src;
 
                 for (i=len; i>0; i--) 
                         d[i-1] = s[i-1];
         }
 
         return dest;
}

void	strcpy	(char *d, const char *s)	{
	do {
		*d++	= *s;
	} while(*s++);
}

int		strlen	(const char *s)	{
	int		len	= 0;
	while(*s++)
		len++;

	return	len;

}
