#include "pmm.h"
#include "multiboot.h"
#include "types.h"

#define PAGE_SIZE	4096
#define BITMAP_SIZE	32768

//	all memory in protected mode
//		= 0xFFFFFFFF
//	page index
//		= address / 0x1000 (2**12)		= max 2**20 1048576
//	bitmap array index
//		= address / 0x1000 / 32 (2**5)	= max 2**15 32768
//	

static	uint32_t	bitmap[BITMAP_SIZE];

extern	const void	kernel_start;
extern	const void	kernel_end;

int		pmm_init	(struct mb_info_t *mb_info)	{
	uint32_t i;

	// memory map
	struct mb_mmap_t*	mmap		= (struct mb_mmap_t*) mb_info->mmap_addr;
	struct mb_mmap_t*	mmap_end	= (void*)((uintptr_t)mb_info->mmap_addr + mb_info->mmap_length);
	struct mb_module_t	*modules	= (void *)mb_info->mods_addr;

	//	clear
	for (i = 0; i < ARRAY_SIZE(bitmap) ; i ++)
		bitmap[i]	= 0x0;

	//	use memory map via multiboot
	while (mmap < mmap_end) {
    		if (mmap->type == 1) {
        		uintptr_t addr		= mmap->base;
        		uintptr_t end_addr	= addr + mmap->length;
 
        		while (addr < end_addr) {
            			pmm_free((void*) addr);
            			addr += 0x1000;
        		}
    		}
		mmap++;
	}

	//	memory struct mark
	pmm_mark_used(mb_info);
	pmm_mark_used(modules);

	//	kernel address mark
	uintptr_t addr = (uintptr_t) &kernel_start;
	while (addr < (uintptr_t) &kernel_end) {
    		pmm_mark_used((void*) addr);
    		addr += 0x1000;
	}

	//	module address mark
	for (i=0; i<mb_info->mods_count; i++) {
		addr = modules[i].mod_start;
		while (addr < modules[i].mod_end) {
			pmm_mark_used((void*)addr);
			addr += 0x1000;
		}
	}

	return 0;
}

void	*pmm_alloc	(void)
{
	uint32_t	i, j;

	//	all check
	for (i = 0 ; i < ARRAY_SIZE(bitmap) ; i++) {
		//	unused memory?
		if (bitmap[i]	!= 0) {
			for (j = 0 ; j < 32 ; j++) {
				if (bitmap[i] & (1 << j)) {
					bitmap[i]	&= ~(1 << j);
					return	(void*)((i*32+j) * PAGE_SIZE);
				}
			}
		}
	}

	return	NULL;
}

void	pmm_free	(void* addr)	{
	uint32_t index	= (uint32_t)addr / PAGE_SIZE;
	bitmap[index / 32]	|= (1 << (index % 32));	
//	kprintf("%x", bitmap[index/32]);
//	kprintf("%x", index);
}

void	pmm_mark_used	(void* addr)	{
	uint32_t index	= (uint32_t)addr / PAGE_SIZE;
	bitmap[index / 32]	&= ~(1 << (index % 32));
}

uint32_t	pmm_free_pages	(void)	{
	uint32_t	i, ctr=0;
	uint8_t		j;

	for (i=0 ; i < ARRAY_SIZE(bitmap) ; i++) {
		if (bitmap[i]	!= 0) {
			for (j=0 ; j<32 ; j++) {
				if (bitmap[i] & (1<<j))
					ctr++;
			}
		}
	}
	
	return	ctr;
}

uint32_t	pmm_used_pages	(void)	{
	return	BITMAP_SIZE - pmm_free_pages();
}

int		pmm_test	(uint32_t test_length)	{
	uint32_t i, ctr = 0, *ptr[test_length];

	for(i=0 ; i < test_length ; i++)
		ptr[i] = (uint32_t*)pmm_alloc();

	for(i=0 ; i < test_length - 1 ; i++) {
		if(((uint32_t)ptr[i+1]-(uint32_t)ptr[i])	== 4096)
			ctr++;
	}
	
	for(i=0 ; i < test_length	; i++)
		pmm_free(ptr[i]);
	
	if(ctr	== test_length-1)
		return	0;
	
	return	1;	
}

//bit 1 = 1* 4096
//bit 2 = 2* 4096
//addr / 0x1000 / 32 == arrayindex
//(addr / 0x1000) / (addr / 4096 / 32) bitposition

//Bit Operations:
//if bit is set : (x & (1 << bitnumber))
//unset bit     : (x |= (1 << bitnumber))
//set bit       : (x &= b(1 << bitnumber))
