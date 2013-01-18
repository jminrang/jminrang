#include "asm.h"

inline	void	outb(uint16_t port, uint8_t data) {
    asm	volatile	("outb	%0,	%1" ::"a"(data), "Nd"(port));
}

inline	uint8_t	inb(uint16_t port)	{
	uint8_t	v;
	asm	volatile	("inb	%1,	%0" :"=a"(v):"Nd"(port));
	return	v;
}
