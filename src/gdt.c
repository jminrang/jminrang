#include "gdt.h"
#include "types.h"

static	uint64_t	gdt[6];
extern	uint32_t	tss[32];

void	gdt_init	(void)	{
	gdt_entry_init(0,0,0,		0);
	gdt_entry_init(1,0,0xFFFFF,	GDT_F_SEG		|
								GDT_F_32BIT		|
								GDT_F_CODE_SEG	|
								GDT_F_4K_GRAN	|
								GDT_F_P			);
	gdt_entry_init(2,0,0xFFFFF,	GDT_F_SEG		|
								GDT_F_32BIT		|
								GDT_F_DATA_SEG	|
								GDT_F_4K_GRAN	|
								GDT_F_P			);
	gdt_entry_init(3,0,0xFFFFF,	GDT_F_SEG		|
								GDT_F_32BIT		|
								GDT_F_CODE_SEG	|
								GDT_F_4K_GRAN	|
								GDT_F_P			|
								GDT_F_RING_3	);
	gdt_entry_init(4,0,0xFFFFF,	GDT_F_SEG		|	
								GDT_F_32BIT		|
								GDT_F_CODE_SEG	|
								GDT_F_4K_GRAN	|
								GDT_F_P			|
								GDT_F_RING_3	);
	gdt_entry_init(5,(uint32_t) tss, sizeof(tss),	GDT_F_TSS	|
													GDT_F_P		|
													GDT_F_RING_3);
	gdtr.limit		= 6 * 8 -1;
	gdtr.pointer	= gdt;

	asm	volatile	("lgdt	%0"::"m" (gdtr));
	asm	volatile	("ljmp	$0x08,	$.1		\n\t"
					 ".1:					\n\t"
					 "mov	$0x10,	%%ax	\n\t"
					 "mov	%%ax,	%%ds	\n\t"
					 "mov	%%ax,	%%es	\n\t"
					 "mov	%%ax,	%%ss		":::"eax");

	asm	volatile	("ltr	%%ax"::"a"(5<<3));

}

void	gdt_entry_init	(int32_t i,			uint32_t base,
						 uint32_t limit,	int32_t flags)	{
	gdt[i]	= limit	& 0xFFFFLL;
	gdt[i]	|= (base & 0xFFFFFFLL)		<< 16;
	gdt[i]	|= (flags & 0xFFLL)			<< 40;
	gdt[i]	|= ((limit >> 16) & 0xFLL )	<< 48;
	gdt[i]	|= ((flags >> 8 ) & 0xFFLL)	<< 52;
	gdt[i]	|= ((base  >> 24) & 0xFFLL)	<< 56;

}
