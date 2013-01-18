#ifndef	__RTC_H__
#define	__RTC_H__

#include "types.h"

void		get_cmos_time	(void);

uint8_t		rtc_cmos_read	(uint8_t addr);
void		rtc_cmos_write	(uint8_t val, uint8_t addr);
uint32_t	bcd2bin			(uint8_t val);
uint32_t	bcd2bin_hour	(uint8_t val);
uint8_t		bin2bcd			(uint32_t val);

struct time	{
	uint32_t	year;
	uint32_t	mon;
	uint32_t	day;
	uint32_t	hour;
	uint32_t	min;
	uint32_t	sec;
}t;

#endif
