#ifndef HEADER_MEMORY
#define HEADER_MEMORY

#include "multiboot.h"
#include "asm_utils.h"
#include "setup.h"
#include "video.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct memory_area_t {
	unsigned long long start_address;
	unsigned long long end_address;
	unsigned long memory_type;
	struct memory_area_t* next_area;
};

struct memory_hole_t {
	unsigned long start;
	unsigned long end;
	struct memory_hole_t* next;
};

extern struct memory_area_t video_framebuffer_memory;

void memory_read_from_bootloader(multiboot_info_t* mbinfo, char* scratch_memory);
void* memory_kalloc(unsigned long amount);
void memory_kfree(void* ptr);
struct memory_area_t* memory_get_memory_map();
struct memory_hole_t* memory_get_holes();

#endif