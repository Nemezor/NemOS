#include "video.h"

struct gfx_config_t* config;

void video_read_from_bootloader(multiboot_info_t* mbinfo, char* scratch_memory) {
	struct vbe_mode_info_t* info;
	if ((mbinfo->flags & 0x800) == 0x800) {
		info = (struct vbe_mode_info_t*)mbinfo->vbe_mode_info;
		config = (struct gfx_config_t*)scratch_memory;

		config->framebuffer = (char*)info->framebuffer;
		config->blue_mask = _video_to_bits(info->blue_mask);
		config->red_mask = _video_to_bits(info->red_mask);
		config->green_mask = _video_to_bits(info->green_mask);
		config->undef_mask = _video_to_bits(info->reserved_mask);
		config->blue_position = info->blue_position;
		config->red_position = info->red_position;
		config->green_position = info->green_position;
		config->undef_position = info->reserved_position;
		config->blue_bits = _video_color_precision(info->blue_mask);
		config->red_bits = _video_color_precision(info->red_mask);
		config->green_bits = _video_color_precision(info->green_mask);
		config->undef_bits = _video_color_precision(info->reserved_mask);
		config->line_size = info->pitch;
		config->pixel_size = info->bpp / 8;
		if (info->bpp % 8 > 0) {
			config->pixel_size++;
		}
		config->height = info->height;
		config->width = info->width;

		video_framebuffer_memory.memory_type = 10;
		video_framebuffer_memory.next_area = NULL;
		video_framebuffer_memory.start_address = (unsigned long)config->framebuffer;
		video_framebuffer_memory.end_address = (unsigned long)config->framebuffer + config->line_size * config->height;
		
		gfx_initialize_graphics(config);
	}else{
		__asm_utils_hang();
	}
}

unsigned long _video_to_bits(char count) {
	long ret = 1;
	if (count == 0) {
		return 0;
	}
	for (char c = 0; c < count - 1; c++) {
		ret |= ret << 1;
	}
	return ret;
}

unsigned long _video_color_precision(unsigned long bits) {
	unsigned long pow = 1;
	for (long c = 0; c < (8 - (long)bits); c++) {
		pow *= 2;
	}
	return pow;
}