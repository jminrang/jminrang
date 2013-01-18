#ifndef	__GDT_H__
#define	__GDT_H__

#include "types.h"

#define	GDT_F_DATA_SEG	0x02
#define	GDT_F_CODE_SEG	0x0A
#define	GDT_F_TSS		0x09
#define	GDT_F_SEG		0x10
#define	GDT_F_RING_0	0x00
#define	GDT_F_RING_3	0x60
#define	GDT_F_P			0x80
#define	GDT_F_4K_GRAN	0x800
#define	GDT_F_32BIT		0x400

struct	{	
	uint16_t	limit;
	void*	pointer;
} __attribute__((packed)) gdtr;

void	gdt_init		(void);

void	gdt_entry_init	(int32_t i,		 uint32_t base,
						 uint32_t limit, int32_t flags);

#endif
