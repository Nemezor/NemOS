#ifndef HEADER_VIDEO
#define HEADER_VIDEO

#include "multiboot.h"
#include "asm_utils.h"
#include "vbe.h"
#include "memory.h"
#include "gfx.h"
#include <stdbool.h>

void video_read_from_bootloader(multiboot_info_t* mbinfo, char* scratch_memory);
unsigned long _video_to_bits(char count);
unsigned long _video_color_precision(unsigned long bits);

#endif