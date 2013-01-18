#ifndef CONSOLE_H
#define CONSOLE_H

#include "stdint.h"
#include "types.h"
#include "asm.h"

#define COLS 80U
#define ROWS 25U

#define TEXTMODE_TABSIZE 8

// textattributes
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define GREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define GETX (gpos % COLS)
#define GETY ((gpos - GETX) / COLS)

void set_attribut(uint8_t vogr, uint8_t higr);
uint16_t attribut(uint8_t fore,uint8_t back);
void gotoxy(uint8_t x,uint8_t y);
void move_cursor(void);
void scroll_down(void);
void putch(char ch);
void puts(char *s);
void clear_screen(void);
void text_out(uint8_t *text, uint8_t xpos, uint8_t ypos);
void text_out_color(uint8_t *text, uint8_t xpos, uint8_t ypos, uint8_t fore, uint8_t back );
uint8_t getypos(void);
uint8_t getxpos(void);
void kprintf(char *format,...);
void scroll_down(void);

#endif
