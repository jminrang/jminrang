#ifndef	__IDT_H__
#define	__IDT_H__

#include "types.h"

#define	IDT_T_TASK	0x05
#define	IDT_T_INT	0x06
#define	IDT_T_TRAP	0x07
#define	IDT_T_32BIT	0x08
#define	IDT_RING_0	0x00
#define	IDT_RING_3	0x60
#define	IDT_E_P		0x80

struct	{
	uint16_t	limit;
	void*		pointer;
} __attribute__((packed)) idtr;

struct	regs_t	{
	uint32_t	eax;
	uint32_t	ebx;
	uint32_t	ecx;
	uint32_t	edx;
	uint32_t	esi;
	uint32_t	edi;
	uint32_t	ebp;

	uint32_t	int_no;
	uint32_t	error;

	uint32_t	eip;
	uint32_t	cs;
	uint32_t	eflags;
	uint32_t	esp;
	uint32_t	ss;
};

void	idt_init	(void);
struct  regs_t* interrupt_handler   (struct regs_t* cpu); 


#endif
