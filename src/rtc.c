#include "rtc.h"
#include "asm.h"

#define	RTC_PORT(x)	(0x70 + x)

void	get_cmos_time	(void)	{

	while(rtc_cmos_read(0x0A) & 0x80);

	t.sec	= rtc_cmos_read(0x00);
	t.min	= rtc_cmos_read(0x02);
	t.hour	= rtc_cmos_read(0x04);
	t.day	= rtc_cmos_read(0x07);
	t.mon	= rtc_cmos_read(0x08);
	t.year	= rtc_cmos_read(0x09);

	if(!(rtc_cmos_read(0x0B) & 0x04 ))	{
		t.sec	= bcd2bin(t.sec);
		t.min	= bcd2bin(t.min);
		t.hour	= bcd2bin_hour(t.hour);
		t.day	= bcd2bin(t.day);
		t.mon	= bcd2bin(t.mon);
		t.year	= bcd2bin(t.year);
	}
}

uint8_t		rtc_cmos_read	(uint8_t addr)	{
	uint8_t	val;
	outb(RTC_PORT(0), addr);
	val	= inb(RTC_PORT(1));
	return val;
}

void		rtc_cmos_write	(uint8_t val, uint8_t addr)	{
	outb(addr, RTC_PORT(0));
	outb(val, RTC_PORT(1));
}

uint32_t	bcd2bin	(uint8_t val)	{
	return	(val & 0x0F) + ((val >> 4) & 0x0F) * 10;
}

uint32_t	bcd2bin_hour	(uint8_t val)	{
	return	(val & 0x0F) + ((val >> 4) & 0x0F) * 10 + 9;
}

uint8_t		bin2bcd	(uint32_t val)	{
	return	((val / 10) << 4) + val % 10;
}
