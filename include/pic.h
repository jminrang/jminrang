#ifndef	__PIC_H__
#define	__PIC_H__

#include "types.h"

void	pic_init		(void);
void	pic_mask_irq	(uint16_t mask);
void	pic_send_end_int(uint32_t irq_num);

#endif
