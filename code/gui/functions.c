#include "functions.h"

char _draw_number(long long num, long x, long y, long color) {
	long long copy = num;
	char counter = 0;
	char length = 0;
	while (copy != 0) {
		copy /= 10;
		counter++;
	}
	copy = num;
	length = counter;
	while (copy != 0) {
		counter--;
		font_draw_char((unsigned char)(copy % 10) + 48, x + counter * 8, y, color);
		copy /= 10;
	}
	return length;
}

void gui_functions_menu_1_item_1() {
	struct memory_area_t* map = memory_get_memory_map();
	struct memory_area_t* current = map;
	long long total_amount = 0;
	long long highest_address = 0;

	do {
		total_amount += (current->end_address - current->start_address);
		if (current->end_address > (unsigned long long)highest_address) {
			highest_address = (long long)current->end_address;
		}
		current = current->next_area;
	} while (current != NULL);
	current = map;

	long index = 700;
	font_draw_string("Total:", index, 10, 0xffffff);
	index += 7*8;
	index += _draw_number(total_amount / (1024*1024), index, 10, 0xffffff) * 8;
	font_draw_string(" MiB (", index, 10, 0xffffff);
	index += 6*8;
	index += _draw_number(total_amount, index, 10, 0xffffff) * 8;
	font_draw_string(" B)", index, 10, 0xffffff);

	gfx_draw_rectangle_filled(700, 25, 500, 670, 0x404040);

	do {
		long begin = (long)(current->start_address * 670 / highest_address);
		long end = (long)(current->end_address * 670 / highest_address);

		if (current->memory_type == 1) {
			gfx_draw_rectangle_filled(700, 695 - end, 500, end - begin, 0x007708);
		}else{
			gfx_draw_rectangle_filled(700, 695 - end, 500, end - begin, 0xba0000);
		}

		current = current->next_area;
	} while (current != NULL);

	struct memory_hole_t* holes = memory_get_holes();
	struct memory_hole_t* current_hole = holes;

	do {
		long begin = (long)((unsigned long long)current_hole->start * 670 / highest_address);
		long end = (long)((unsigned long long)current_hole->end * 670 / highest_address);

		gfx_draw_rectangle_filled(700, 695 - end, 500, end - begin, 0x00d20f);

		current_hole = current_hole->next;
	} while (current_hole != NULL);
}

void gui_functions_menu_1_item_2() {
	font_draw_string(cpuid_get_info()->vendor_string, 700, 10, 0xffffff);
}

void gui_functions_menu_2_item_1() {
	font_draw_string("TODO: ACPI, PCI, AHCI", 700, 10, 0xffffff);
}