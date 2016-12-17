#include "gfx.h"

struct gfx_config_t* config;

void gfx_initialize_graphics(struct gfx_config_t* gfx_config) {
	config = gfx_config;

	gfx_draw_image(splash_screen_data, 0, 0, 1280, 720);
}

void gfx_draw_line(long x1, long y1, long x2, long y2, unsigned long color) {
	long _x1 = x1 < x2 ? x1 : x2;
	long _x2 = x1 < x2 ? x2 : x1;
	long _y1 = y1 < y2 ? y1 : y2;
	long _y2 = y1 < y2 ? y2 : y1;
	long width = _x2 - _x1;
	long height = _y2 - _y1;
	long temp;

	if (width >= height) {
		for (long x = 0; x <= _x2; x++) {
			temp = x * config->width / width * height / config->width;
			gfx_draw_point(x + _x1, temp + _y1, color);
		}
	}else{
		for (long y = 0; y <= _y2; y++) {
			temp = y * config->height / height * width / config->height;
			gfx_draw_point(temp + _x1, y + _y1, color);
		}
	}
}

void gfx_draw_image(unsigned long* image, long x, long y, long img_width, long img_height) {
	if (config->width <= x || config->height <= y) {
		return;
	}
	long img_x = x < 0 ? -x : 0;
	long img_y = y < 0 ? -y : 0;
	long img_w = (x + img_width) > config->width ? (config->width - x) : img_width;
	long img_h = (y + img_height) > config->height ? (config->height - y) : img_height;
	long img_step = img_width - img_w;
	long line_step = (config->width - img_w) * config->pixel_size;
	x = (x < 0 ? 0 : x) * config->pixel_size + (y < 0 ? 0 : y) * config->pixel_size * config->width;
	y = img_x + img_y * img_width;

	for (long j = 0; j < img_h; j++) {
		for (long l = 0; l < img_w; l++) {
			_gfx_put_pixel(x, image[y]);

			x += config->pixel_size;
			y++;
		}
		x += line_step;
		y += img_step;
	}
}

void gfx_draw_bitmap(unsigned char* bitmap, long x, long y, long img_width, long img_height, long color) {
	if (config->width <= x || config->height <= y) {
		return;
	}
	long img_x = x < 0 ? -x : 0;
	long img_y = y < 0 ? -y : 0;
	long img_w = (x + img_width) > config->width ? (config->width - x) : img_width;
	long img_h = (y + img_height) > config->height ? (config->height - y) : img_height;
	long img_step = img_width - img_w;
	long line_step = (config->width - img_w) * config->pixel_size;
	x = (x < 0 ? 0 : x) * config->pixel_size + (y < 0 ? 0 : y) * config->pixel_size * config->width;
	y = img_x + img_y * img_width;

	for (long j = 0; j < img_h; j++) {
		for (long l = 0; l < img_w; l++) {
			_gfx_put_pixel(x, bitmap[y] == 1 ? color : 0);

			x += config->pixel_size;
			y++;
		}
		x += line_step;
		y += img_step;
	}
}

void gfx_draw_bitmap_transparent(unsigned char* bitmap, long x, long y, long img_width, long img_height, long color) {
	if (config->width <= x || config->height <= y) {
		return;
	}
	long img_x = x < 0 ? -x : 0;
	long img_y = y < 0 ? -y : 0;
	long img_w = (x + img_width) > config->width ? (config->width - x) : img_width;
	long img_h = (y + img_height) > config->height ? (config->height - y) : img_height;
	long img_step = img_width - img_w;
	long line_step = (config->width - img_w) * config->pixel_size;
	x = (x < 0 ? 0 : x) * config->pixel_size + (y < 0 ? 0 : y) * config->pixel_size * config->width;
	y = img_x + img_y * img_width;

	for (long j = 0; j < img_h; j++) {
		for (long l = 0; l < img_w; l++) {
			if (bitmap[y] == 1) {
				_gfx_put_pixel(x, color);
			}

			x += config->pixel_size;
			y++;
		}
		x += line_step;
		y += img_step;
	}
}

void gfx_draw_rectangle(long x, long y, long width, long height, unsigned long color) {
	if (x >= config->width || y >= config->height || width <= 0 || height <= 0) {
		return;
	}
	long x1 = x < 0 ? 0 : x;
	long y1 = y < 0 ? 0 : y;
	long x2 = (width + x) >= config->width ? config->width : (width + x);
	long y2 = (height + y) >= config->height ? config->height : (height + y);
	long index = x1 * config->pixel_size + y1 * config->line_size;
	long line_step = config->line_size - (x2 - x1 + 1) * config->pixel_size;
	long internal_width = (x2 - x1) * config->pixel_size;

	for (long i = x1; i < x2; i++) {
		_gfx_put_pixel(index, color);
		index += config->pixel_size;
	}
	index += line_step;

	for (long j = y1 + 1; j < y2 - 1; j++) {
		_gfx_put_pixel(index, color);
		index += internal_width;
		_gfx_put_pixel(index, color);
		index += config->pixel_size;
		index += line_step;
	}

	for (long i = x1; i < x2; i++) {
		_gfx_put_pixel(index, color);
		index += config->pixel_size;
	}
}

void gfx_draw_rectangle_filled(long x, long y, long width, long height, unsigned long color) {
	if (x >= config->width || y >= config->height || width <= 0 || height <= 0) {
		return;
	}
	long x1 = x < 0 ? 0 : x;
	long y1 = y < 0 ? 0 : y;
	long x2 = (width + x) >= config->width ? config->width : (width + x);
	long y2 = (height + y) >= config->height ? config->height : (height + y);
	long index = x1 * config->pixel_size + y1 * config->line_size;
	long line_step = config->line_size - (x2 - x1) * config->pixel_size;

	for (long j = y1; j < y2; j++) {
		for (long i = x1; i < x2; i++) {
			_gfx_put_pixel(index, color);
			index += config->pixel_size;
		}
		index += line_step;
	}
}

void gfx_draw_point(long x, long y, unsigned long color) {
	long position = x * config->pixel_size + y * config->line_size;
	if (position >= config->height * config->line_size || position < 0) {
		return;
	}
	_gfx_put_pixel(position, color);
}

inline void _gfx_put_pixel(unsigned long offset, unsigned long argb) {
	unsigned long color = 0;
	color |= ((((argb >> 16) & 0xFF) / config->red_bits) & config->red_mask) << config->red_position;
	color |= ((((argb >> 8) & 0xFF) / config->green_bits) & config->green_mask) << config->green_position;
	color |= (((argb & 0xFF) / config->blue_bits) & config->blue_mask) << config->blue_position;

	if (config->pixel_size == 1) {
		config->framebuffer[offset + 0] = (char)color;
	}else if (config->pixel_size == 2) {
		config->framebuffer[offset + 0] = (char)color;
		config->framebuffer[offset + 1] = (char)(color >> 8);
	}else if (config->pixel_size == 3) {
		config->framebuffer[offset + 0] = (char)color;
		config->framebuffer[offset + 1] = (char)(color >> 8);
		config->framebuffer[offset + 2] = (char)(color >> 16);
	}else{
		config->framebuffer[offset + 0] = (char)color;
		config->framebuffer[offset + 1] = (char)(color >> 8);
		config->framebuffer[offset + 2] = (char)(color >> 16);
		config->framebuffer[offset + 3] = (char)(color >> 24);
	}
}