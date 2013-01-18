#include "cpu_check.h"
#include "console.h"
#include "types.h"

uint32_t	cpu_vendor[3];
struct cpu_features	cpu;

void	cpu_check	(void)	{

	uint32_t	max_level, max_amd_level;
	uint32_t	tfms;
	asm	volatile	("cpuid"
					:"=a" (max_level),
					 "=b" (cpu_vendor[0]),
					 "=d" (cpu_vendor[1]),
					 "=c" (cpu_vendor[2])
					:"a"(0));

	if(max_level >= 0x00000001 && max_level <= 0x0000FFFF)	{
		asm	volatile	("cpuid"
						:"=a" (tfms),
						 "=c" (cpu.flags[4]),
						 "=d" (cpu.flags[0])
						:"a" (0x00000001)
						:"ebx");
		cpu.level	= (tfms >> 8) & 15;
		cpu.model	= (tfms >> 4) & 15;
		if(cpu.level >= 6)
			cpu.model	+= ((tfms >> 16) & 0x0F) << 4;
	}

	asm	volatile	("cpuid"
					:"=a"(max_amd_level)
					:"a" (0x80000000)
					:"ebx", "ecx", "edx");

	if(max_amd_level >= 0x80000001 && max_amd_level <= 0x8000FFFF)	{
		uint32_t	eax	= 0x80000001;
		asm volatile	("cpuid"
						:"+a"(eax),
						 "=c"(cpu.flags[6]),
						 "=d"(cpu.flags[1])
						::"ebx");
	}
}
