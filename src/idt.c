#include "console.h"
#include "pic.h"
#include "idt.h"
#include "timer.h"
#include "kb.h"
#include "asm.h"
#include "string.h"
#include "types.h"

extern void	isr0();
extern void	isr1();
extern void	isr2();
extern void	isr3();
extern void	isr4();
extern void	isr5();
extern void	isr6();
extern void	isr7();
extern void	isr8();
extern void	isr9();
extern void	isr10();
extern void	isr11();
extern void	isr12();
extern void	isr13();
extern void	isr14();
extern void	isr15();
extern void	isr16();
extern void	isr17();
extern void	isr18();
extern void	isr19();
extern void	isr20();
extern void	isr21();
extern void	isr22();
extern void	isr23();
extern void	isr24();
extern void	isr25();
extern void	isr26();
extern void	isr27();
extern void	isr28();
extern void	isr29();
extern void	isr30();
extern void	isr31();

extern void	irq32();
extern void	irq33();
extern void	irq34();
extern void	irq35();
extern void	irq36();
extern void	irq37();
extern void	irq38();
extern void	irq39();
extern void	irq40();
extern void	irq41();
extern void	irq42();
extern void	irq43();
extern void	irq44();
extern void	irq45();
extern void	irq46();
extern void	irq47();

static uint64_t	idt[256];
uint32_t		tss[32]	= { 0, 0, 0x10};

static const void	(*isr[])	= {
	isr0,  isr1,  isr2,  isr3,  isr4,  isr5,  isr6,  isr7,
	isr8,  isr9,  isr10, isr11, isr12, isr13, isr14, isr15,
	isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23,
	isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31,

	irq32, irq33, irq34, irq35, irq36, irq37, irq38, irq39,
	irq40, irq41, irq42, irq43, irq44, irq45, irq46, irq47,
};

void	idt_entry_init	(int32_t	index,	uint32_t	base,
						 uint16_t	sel,	uint8_t		flags)	{
	idt[index]	=	( base	& 0xFFFFLL)					|
					( sel	& 0xFFFFLL)			<< 16	|
					( flags	& 0xFFLL)			<< 40	|
					( (base >> 16) & 0xFFFFLL)	<< 48;
}

void	idt_init	(void)	{
	int		i;
	for(i = 0 ; i < ARRAY_SIZE(isr) ; i++)
		idt_entry_init(i, (uint32_t)isr[i], 0x08,	IDT_T_INT	|
													IDT_T_32BIT	|
													IDT_RING_0	|
													IDT_E_P);
//	software interrupt non;

	idtr.limit	= 256 * 8 - 1;
	idtr.pointer= idt;
	asm	volatile	("lidt	%0"::"m"(idtr));
}

struct	regs_t*	interrupt_handler	(struct	regs_t*	cpu)	{
	struct	regs_t*	new	= cpu;
	if(cpu->int_no	< 31)	{
		//non
		kprintf("\n\n\n Exeception %d \n", cpu->int_no);
		while(1){
			asm	volatile("cli");
			asm	volatile("hlt");
		}
	} else if(cpu->int_no <= 47)	{
		// irq
		if(cpu->int_no	== 0x20)	{
			timer_irq();
			return	new;
		}
		if(cpu->int_no	== 0x21)	{
			kb_irq();
			return	new;
		}
		if(cpu->int_no	>= 0x22)	//don't pit
			kprintf("IRQ	%d\n", cpu->int_no);
		pic_send_end_int(cpu->int_no - 0x20);
	} else	{
		kprintf("int	%d\n", cpu->int_no);
	}

	if(cpu->int_no	== 32)	{
		// software interrupt
	}

	return new;
}
