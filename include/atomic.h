#ifndef	__ATOMIC_H__
#define	__ATOMIC_H__

#include "asm.h"

//	refer by linux

typedef struct	{
	 volatile int	counter;
} atomic_t;

#define	ATOMIC_INIT(i)	{ (i) }
#define	atomic_read(v)	((v) -> counter)
#define	atomic_set(v,i)	(((v)->counter) = (i))

static inline	void	atomic_add	(int	i, atomic_t	*v)	{
	asm	volatile	("lock			 \n\t"
					 "addl	%1,	%0"
					:"=m" (v->counter)
					:"ir" (i), "m" (v->counter));
}

static inline	void	atomic_sub	(int	i, atomic_t	*v)	{
	asm	volatile	("lock			 \n\t"
					 "subl	%1,	%0"
					:"=m" (v->counter)
					:"ir" (i), "m" (v->counter));
}

static inline	int		atomic_sub_and_test	(int	i, atomic_t	*v)	{
	unsigned char	c;

	asm	volatile	("lock			\n\t"
					 "subl	%2,	%0	\n\t"
					 "sete	%1"
					:"=m" (v->counter), "=qm" (c)
					:"ir" (i), "m" (v->counter)
					:"memory");
	return	c;
}

static inline	void	atomic_inc	(atomic_t	*v)	{
	asm	volatile	("lock			\n\t"
					 "incl	%0"
					:"=m"	(v->counter)
					:"m"	(v->counter));
}

static inline	void	atomic_dec	(atomic_t	*v)	{
	asm	volatile	("lock			\n\t"
					 "decl	%0"
					:"=m"	(v->counter)
					:"m"	(v->counter));
}

static inline	int		atomic_dec_and_test	(atomic_t	*v)	{
	unsigned char	c;

	asm	volatile	("lock			\n\t"
					 "decl	%0		\n\t"
					 "sete	%1		\n\t"
					:"=m" (v->counter), "=qm" (c)
					:"m" (v->counter)
					:"memory");

	return	c != 0;
}

static inline	int		atomic_inc_and_test	(atomic_t	*v)	{
	unsigned char	c;

	asm	volatile	("lock			\n\t"
					 "incl	%0	\n\t"
					 "sets	%1"
					:"=m" (v->counter), "=qm" (c)
					:"m" (v->counter)
					:"memory");
	
	return	c != 0;
}

#endif
