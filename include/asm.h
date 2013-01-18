#ifndef __ASM_H__
#define __ASM_H__

#include "types.h"

inline void		outb	(uint16_t port, uint8_t data);
inline uint8_t	inb		(uint16_t port);

#endif
