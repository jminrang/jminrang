#ifndef	__CPU_CHECK_H__
#define	__CPU_CHECK_H__

#include "types.h"

struct	cpu_features	{
	uint32_t	level;
	uint32_t	model;
	uint32_t	flags[10];
};

void	cpu_check	(void);

#endif
