#include "memory.h"

struct memory_area_t* mmap = NULL;
struct memory_hole_t* holes = NULL;
struct memory_hole_t* last_hole = NULL;
struct memory_area_t video_framebuffer_memory;

void memory_read_from_bootloader(multiboot_info_t* mbinfo, char* scratch_memory) {
	if ((mbinfo->flags & 0x40) == 0x40) {
		struct memory_area_t* current = mmap;
		unsigned long ptr = mbinfo->mmap_addr;
		memory_map_t* memmap;

		do {
			memmap = (memory_map_t*)ptr;

			if (mmap == NULL) {
				current = (struct memory_area_t*)(scratch_memory + sizeof(struct gfx_config_t));
				mmap = current;
			}else{
				if (current->next_area == NULL) {
					current->next_area = (struct memory_area_t*)(current + sizeof(struct memory_area_t));
					current = current->next_area;
				}else{
					__asm_utils_hang();
				}
			}
			current->start_address = ((long long)memmap->base_addr_high << 32) | ((long long)memmap->base_addr_low);
			current->end_address = current->start_address + (((long long)memmap->length_high << 32) | ((long long)memmap->length_low));
			current->memory_type = memmap->type;
			current->next_area = NULL;

			ptr += memmap->size + sizeof(long);
		} while (ptr < mbinfo->mmap_addr + mbinfo->mmap_length);
		current->next_area = &video_framebuffer_memory;

		struct memory_area_t* mem = mmap;
		struct memory_hole_t* current_hole = NULL;

		while (mem != NULL) {
			if (mem->memory_type == 1) {
				if (holes == NULL) {
					// TODO: dont assume the first usable memory block is big enough
					if (mem->start_address > (unsigned long)&__lnk_kernel_end) {
						holes = (struct memory_hole_t*)(unsigned long)mem->start_address;
					}else{
						holes = (struct memory_hole_t*)(unsigned long)&__lnk_kernel_end;
					}
					current_hole = holes;
					current_hole->start = (unsigned long)current_hole + 1048576; // 1MiB
					current_hole->end = mem->end_address;
					current_hole->next = NULL;
				}else{
					current_hole->next = (struct memory_hole_t*)((long)current_hole + sizeof(struct memory_hole_t));
					current_hole = current_hole->next;
					current_hole->start = mem->start_address;
					current_hole->end = mem->end_address;
					current_hole->next = NULL;
				}
			}
			mem = mem->next_area;
		}
	}
}

void* memory_kalloc(unsigned long size) {
	if (size <= 0) {
		return NULL;
	}
	size += 4;
	struct memory_hole_t* current = holes;
	struct memory_hole_t* smallest = NULL;
	struct memory_hole_t* previous = NULL;
	struct memory_hole_t* prevsmallest = NULL;

	while (current != NULL) {
		if (current->end - current->start == size) {
			smallest = current;
			prevsmallest = previous;
			break;
		}else if (current->end - current->start > size) {
			if (smallest == NULL || current->end - current->start < smallest->end - smallest->start) {
				smallest = current;
				prevsmallest = previous;
			}
		}
		previous = current;
		current = current->next;
	}
	if (smallest == NULL) {
		// out of memory
		__asm_utils_hang();
	}
	void* retptr = (void*)(smallest->start + 4);
	*((unsigned long*)smallest->start) = size;
	smallest->start += size;
	if (smallest->start >= smallest->end) {
		if (prevsmallest == NULL) {
			holes = smallest->next;
		}else{
			prevsmallest->next = smallest->next;
		}
	}
	return retptr;
}

void memory_kfree(void* ptr) {
	if (ptr == NULL) {
		return;
	}
	ptr = (void*)((unsigned long*)ptr - 4);
	long size = *(unsigned long*)ptr;
	struct memory_hole_t* current = holes;
	struct memory_hole_t* start_hole = NULL;
	struct memory_hole_t* end_hole = NULL;
	while (current != NULL) {
		if ((unsigned long)ptr == current->end) {
			start_hole = current;
		}
		if ((unsigned long)ptr + size + 1 == current->start) {
			end_hole = current;
		}
		current = current->next;
		if (end_hole && start_hole) {
			break;
		}
	}
	if (end_hole && start_hole) {
		start_hole->end = end_hole->end;
		start_hole->next = end_hole->next;
	}else if (end_hole) {
		end_hole->start = (unsigned long)ptr;
	}else{
		start_hole->end = (unsigned long)ptr + size;
	}
}

struct memory_area_t* memory_get_memory_map() {
	return mmap;
}

struct memory_hole_t* memory_get_holes() {
	return holes;
}