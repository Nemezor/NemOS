#ifndef HEADER_GFX
#define HEADER_GFX

#include "splash_screen.h"
#include "vbe.h"
#include <stdbool.h>

struct gfx_config_t {
	char* framebuffer;
	unsigned long red_mask;
	unsigned long green_mask;
	unsigned long blue_mask;
	unsigned long undef_mask;
	unsigned long red_position;
	unsigned long green_position;
	unsigned long blue_position;
	unsigned long undef_position;
	unsigned char red_bits;
	unsigned char green_bits;
	unsigned char blue_bits;
	unsigned char undef_bits;
	long width;
	long height;
	long line_size;
	long pixel_size;
};

void gfx_initialize_graphics(struct gfx_config_t* gfx_config);
void gfx_draw_point(long x, long y, unsigned long color);
void gfx_draw_line(long x1, long y1, long x2, long y2, unsigned long color);
void gfx_draw_image(unsigned long* image, long x, long y, long width, long height);
void gfx_draw_bitmap(unsigned char* bitmap, long x, long y, long img_width, long img_height, long color);
void gfx_draw_bitmap_transparent(unsigned char* bitmap, long x, long y, long img_width, long img_height, long color);
void gfx_draw_rectangle(long x, long y, long width, long height, unsigned long color);
void gfx_draw_rectangle_filled(long x, long y, long width, long height, unsigned long color);
void _gfx_put_pixel(unsigned long offset, unsigned long argb);

#endif
