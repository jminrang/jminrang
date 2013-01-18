#ifndef	__VMM_H__
#define __VMM_H__

#include "types.h"
#include "multiboot.h"

#define PAGE_DIRECTORY_LENGTH	1024
#define PAGE_TABLE_LENGTH	 	1024
#define PAGE_SIZE		 		4096

/* tables entries flags */
#define PTE_PRESENT				0x01
#define PTE_WRITE				0x02
#define	PTE_USER				0x04

/* page entries flags */
#define PDE_PRESENT				0x01
#define PDE_WRITE				0x02
#define PDE_USER				0x04

/* memory layout */
#define VMM_USER_START	 		0x40000000 /* start of usercode (1GB mark) */
#define VMM_USER_END			0xffffffff /* 3GB of user space */

struct	vmm_context {
	uint32_t *pagedir;
};

int					vmm_init				(struct mb_info_t *mb_info);
struct vmm_context	*vmm_create_context		(void);
void				vmm_activate_context	(struct vmm_context *context);
int					vmm_map_page			(struct vmm_context *context,
											 uintptr_t virt,
											 uintptr_t phys);


#endif
