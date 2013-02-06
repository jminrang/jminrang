#ifndef __ASM_H__
#define __ASM_H__

#include "types.h"

//	refer by linux	
#define	mb()	asm volatile ("lock; addl $0, 0(%%esp)":::"memory")
#define	rmb()	mb()
#define	wbm()	asm	volatile ("":::"memory")

inline void		outb	(uint16_t port, uint8_t data);
inline uint8_t	inb		(uint16_t port);

#endif
