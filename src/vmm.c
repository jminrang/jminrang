#include "vmm.h"
#include "pmm.h"
#include "multiboot.h"

static struct		vmm_context* kernel_context;

extern const void	kernel_start;
extern const void	kernel_end;

int		vmm_init	(struct mb_info_t *mb_info)	{
	uint32_t	cr0;
	int32_t		i;
 
	// align 4k
	uintptr_t	kernel_start_al	 = ((uintptr_t)&kernel_start) & 0xFFFFF000;
   	kernel_context	= vmm_create_context();
 
	// kernel address
   	for (i = kernel_start_al ; i < (uint32_t)&kernel_end ; i += PAGE_SIZE)
       	vmm_map_page(kernel_context, i, i);

	// video address
	for (i = 0xb8000 ; i <= 0xbffff ; i += PAGE_SIZE)
		vmm_map_page(kernel_context, i, i);

	vmm_activate_context(kernel_context);
 
	asm volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= (1 << 31);
	asm volatile("mov %0, %%cr0" : : "r" (cr0));

	return 0;
}

struct vmm_context*	vmm_create_context	(void)	{
	struct vmm_context*	context	= pmm_alloc();
	uint32_t			i;
 
	context->pagedir	= pmm_alloc();
	for (i = 0; i < 1024; i++)
		context->pagedir[i] = 0;
 
	return	context;
}

int		vmm_map_page	(struct vmm_context* context, uintptr_t virt, uintptr_t phys)	{
	uint32_t	page_index	= virt			/ 0x1000;
	uint32_t	pd_index	= page_index	/ 1024;
 	uint32_t	pt_index	= page_index	% 1024;

	uint32_t*	page_table;
 	int32_t		i;

	//	align 0x1000 = 4k
	if ((virt & 0xFFF) || (phys & 0xFFF))
  		return	-1;

	//	available ?
	if (context->pagedir[pd_index] & PTE_PRESENT) {
		page_table = (uint32_t*) (context->pagedir[pd_index] & ~0xFFF);
	} else {
		//	new
		page_table = pmm_alloc();
		for (i = 0; i < 1024; i++)
			page_table[i] = 0;
		context->pagedir[pd_index] =
				(uint32_t) page_table | PTE_PRESENT | PTE_WRITE;
	}
 
 	//	new page mapping
	page_table[pt_index] = phys | PTE_PRESENT | PTE_WRITE;
	asm volatile("invlpg %0" : : "m" (*(char*)virt));
 
	return 0;
}

void vmm_activate_context(struct vmm_context* context)	{
	asm volatile("mov %0, %%cr3" : : "r" (context->pagedir));
}
