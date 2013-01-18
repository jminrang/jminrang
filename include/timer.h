#ifndef	__TIMER_H__
#define	__TIMER_H__

#include "types.h"

void	timer_init	(uint32_t freq);
void	timer_irq	(void);

#endif
