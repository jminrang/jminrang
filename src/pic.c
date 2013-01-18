#include "pic.h"
#include "asm.h"

void	pic_init	(void)	{
	outb(0x20,	0x11);
	outb(0xA0,	0x11);

	outb(0x21,	0x20);
	outb(0xA1,	0x28);

	outb(0x21,	0x04);
	outb(0xA1,	0x02);

	outb(0x21,	0x01);
	outb(0xA1,	0x01);

	outb(0x21,	(0xFF & ~(1<<2)));
	outb(0xA1,	0xFF);
}

void	pic_mask_irq	(uint16_t	mask)	{
	outb(0x21,	(uint8_t) mask);
	outb(0xA1,	(uint8_t) mask >> 8);
}

void	pic_send_end_int	(uint32_t	irq_num)	{
	outb(0x20,	0x20);
	if(irq_num >= 12)
		outb(0xA0,	0x20);
}