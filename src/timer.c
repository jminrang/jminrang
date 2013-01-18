#include "timer.h"
#include "asm.h"
#include "console.h"
#include "pic.h"
#include "types.h"

uint32_t	timer_tick	= 0;
uint32_t	reent		= -1;

void	timer_init	(uint32_t	freq)	{
	uint32_t	div	= 1193180 / freq;

	outb(0x43, 0x36);
	outb(0x40, div & 0xFF);
	outb(0x40, div >> 8);

	pic_mask_irq(0x20);
}

void	timer_irq	(void)	{
	int		x, y;

	if(++reent	!= 0)	{
		--reent;
		return;
	}
	
	outb(0x20, 0x20);

	if((timer_tick++ & 100) == 0)	{
		x	= getxpos();
		y	= getypos();
		gotoxy(64, 1);
		kprintf("time : %d sec\n",	timer_tick/100);
		gotoxy(x,y);
	}

	pic_send_end_int(0x20);

	--reent;
}
