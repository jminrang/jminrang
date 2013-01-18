#ifndef __PMM_H__
#define __PMM_H__

#include "types.h"
#include "console.h"
#include "multiboot.h"

int			pmm_init		(struct mb_info_t *mb_info);
void*		pmm_alloc		(void);
void		pmm_free		(void* addr);
void		pmm_mark_used	(void* addr);
uint32_t	pmm_free_pages	(void);
uint32_t	pmm_used_pages	(void);
int			pmm_test		(uint32_t test_length);

#endif
