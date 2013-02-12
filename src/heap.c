#include "heap.h"
#include "pmm.h"
#include "vmm.h"
#include "types.h"

extern const void		kernel_end;

uintptr_t				placement	= (uintptr_t)&kernel_end;
uintptr_t				heap_end	= (uintptr_t)NULL;
uintptr_t				*heap		= 0;

uint32_t	kmalloc_int	(uint32_t	size,
						 int32_t	align,
						 uint32_t	*phys)	{
	if(heap	!= 0)	{
	}

	uintptr_t	address	= placement;
	placement	+= size;
	return (uintptr_t) address;
}
