#ifndef HEADER_FONT
#define HEADER_FONT

#include "gfx.h"

unsigned char* font_get_bitmap(char character);
void font_draw_char(char character, long x, long y, long color);
void font_draw_string(char* string, long x, long y, long color);

#endif