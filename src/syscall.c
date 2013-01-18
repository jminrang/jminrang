#include "syscall.h"
#include "types.h"
#include "console.h"

#define	SYS_OPEN	1
#define	SYS_CREATE	2
#define	SYS_READ	3
#define	SYS_WRITE	4
#define	SYS_CLOSE	5

int32_t		sys_open	(void)	{

	return 0;
}
int32_t		sys_create	(void)	{
	return 0;
}
int32_t		sys_read	(void)	{
	return 0;
}
int32_t		sys_write	(void)	{
	return 0;
}
int32_t		sys_close	(void)	{
	return 0;
}

static int32_t	(*syscalls[])	(void)	=	{
	[SYS_OPEN]		= sys_open,
	[SYS_CREATE]	= sys_create,
	[SYS_READ]		= sys_read,
	[SYS_WRITE]		= sys_write,
	[SYS_CLOSE]		= sys_close,
};

void	syscall	(int32_t intr)	{
	int	num;

	num	= intr;

	if(syscalls[num])
		syscalls[num]();
	else	{
		kprintf("unknown syscall number : %d\n", num);
	}
}
