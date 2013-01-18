#ifndef TYPES_H
#define TYPES_H

#define true 1
#define false 0

#define NULL 0

typedef unsigned long long	uint64_t;
typedef signed   long long	int64_t;
typedef unsigned int		uint32_t;
typedef signed   int		int32_t;
typedef unsigned short		uint16_t;
typedef signed   short  	int16_t;
typedef unsigned char		uint8_t;
typedef signed   char 		int8_t;
typedef uint32_t size_t;
typedef uint32_t uintptr_t;

#define	ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))


#endif

