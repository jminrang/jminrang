#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "rtc.h"
#include "timer.h"
#include "kb.h"
#include "cpu_check.h"
#include "pmm.h"
#include "vmm.h"
#include "notice.h"

extern	uint32_t cpu_vendor[3];

void k_main(struct mb_info_t *mb_info)
{
	clear_screen();
	kprintf(START);

	gdt_init();
	kprintf(GDT);

	idt_init();
	kprintf(IDT);

	pic_init();
	timer_init(100);
	kb_init();
//	pic_mask_irq(32);
//	pic_mask_irq(33);

//	asm	volatile	("int	$0x21");
//	asm	volatile	("int	$0x22");

	kprintf(PIC);

	get_cmos_time();
	kprintf(RTC);

	cpu_check();
	kprintf(CPU);

	pmm_init(mb_info);
	kprintf(PMM);

	vmm_init(mb_info);
	kprintf(VMM);

	asm volatile ("sti");

	while(1);
}
