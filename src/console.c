#include "console.h"
#include "string.h"

uint32_t gpos = 0;
uint16_t *pScreen = (uint16_t *) 0xB8000;
uint16_t gattr = 0x0700;

static uint8_t hexmap[] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

uint16_t attribut(uint8_t fore, uint8_t back) {
	uint16_t temp;

	temp = back<<4;
	temp |= fore;
	temp = temp<<8;
	return temp;
}

void set_attribut(uint8_t fore, uint8_t back) {
	gattr = attribut(fore, back);
}

void gotoxy(uint8_t x, uint8_t y) {
	gpos = x + y * COLS;
	move_cursor();
}

void move_cursor(void) {
	outb(0x3D4, 14);
	outb(0x3D5, gpos>>8);
	outb(0x3D4, 15);
	outb(0x3D5, (uint8_t) gpos);
}

void scroll_down() {
	uint16_t blank, temp;
	
	blank = 0x20 | gattr;
	
	if (GETY >= ROWS) {
		temp = GETY - ROWS + 1;
		memcpy(pScreen, pScreen + temp*COLS, (ROWS - temp) * COLS * 2);
		memsetw(pScreen + (ROWS-temp) *COLS, blank, COLS*temp);
		gpos = 1920;
	}
}


void putch(char ch) {
	switch(ch) {
		case '\n': gotoxy(0,GETY+1); break;
		case '\r': gotoxy(0,GETY); break;
		case '\t': gotoxy(GETX<COLS-TEXTMODE_TABSIZE?GETX + TEXTMODE_TABSIZE:GETX, GETY); break;

		case 8:		//backspace
			pScreen[gpos] = (uint16_t) 0;
			break;

		default:
			pScreen[gpos++] = (uint16_t) (ch | gattr);
	}
	scroll_down();
	move_cursor();
}

void puts(char *s) {
	while(*s) putch(*(s++));
}

void clear_screen() {
	uint16_t temp=gattr;
	uint32_t i;

	gattr = 0x00;
	gotoxy(0,0);
	for(i=0; i<=1999; ++i)
		putch(0x00);
	gotoxy(0,0);
	gattr = temp;
}

void text_out(uint8_t *text, uint8_t xpos, uint8_t ypos) {
	uint32_t pos;

	if(xpos>COLS) 
		xpos = COLS;
	if(ypos>ROWS) 
		ypos = ROWS;
	pos = xpos + (ypos * COLS);
	while(*text) {
		pScreen[pos] = (uint16_t) *text | gattr;
		++pos;
		++text;
	}
}

uint8_t getypos(void) {
	return (uint8_t) GETY;
}

uint8_t getxpos(void) {
	return (uint8_t) GETX;
}

void kprintf(char *format,...) {
	uint32_t	*args	= ((uint32_t*) &format) + 1;
	char		*t, d[11], xx[9];

	xx[8]	= 0;
	uint8_t		aktarg=0;
	uint32_t	u;
	int			n, i;

	// first argument in args[0]
	while (*format) {
		if (*format == '%') {
			++format;
			if (*format == 0) break;

			switch (*format) {
				case 's':	//string
					t = (char *) args[aktarg];
					while (*t)
						putch(*t++);
					break;

				case 'c':	//signle character
					putch((char) args[aktarg]);
					break;

				case 'x':	//32 bit hex
					u = args[aktarg];
					putch('0');putch('x');
					for(i=7; i>=0; --i) {
						xx[i]=hexmap[u & 0x0F];
						u >>= 4;
					}
					puts(xx);
					break;

				case 'd':	//sint32_t
					n = args[aktarg];
					if (n < 0) {
						u = -n;
						putch('-');
					} else {
						u = n;
					}

					i=9;
					do {
						d[i--] = (u%10) + '0';
						u /= 10;
					} while (u && i>=0);
					while (++i < 10)
						putch(d[i]);
					break;

				case 'u': 	//unsigned integer
					u = args[aktarg];
					i=9;
					do {
						d[i--] = (u%10) + '0';
						u /= 10;
					} while (u && i>=0);
					while (++i < 10)
						putch(d[i]);
					break;

				case 'X':	//8 bit hex
					putch('0');putch('x');
					n = args[aktarg];
					putch(hexmap[(n & 0xF0) >> 4]);
					putch(hexmap[n & 0x0F]);
					break;

				default:
					putch(*format);
			}
			++aktarg;
		} else {
			putch(*format);
		}
		++format;
	}
}

