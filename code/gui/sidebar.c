#include "sidebar.h"

struct sidebar_item_t {
	char text[35];
	void (*function)();
};

struct sidebar_menu_t {
	long items;
	char text[15];
	struct sidebar_item_t* item_data;
};

struct sidebar_item_t menu_1_items[] = {
	{
		"Memory usage and fragmentation",
		&gui_functions_menu_1_item_1
	},
	{
		"CPU identification (CPUID)",
		&gui_functions_menu_1_item_2
	}
};

struct sidebar_item_t menu_2_items[] = {
	{
		"Boot disk",
		&gui_functions_menu_2_item_1
	}
};

struct sidebar_menu_t menu_data[] = {
	{
		2,
		"System",
		menu_1_items
	},
	{
		1,
		"File Browser",
		menu_2_items
	}
};

long menus = 2;

long current_menu = 0;
long current_item = 0;
long new_menu = 0;
long new_item = 0;
bool in_menu = false;
bool new_in_menu = false;

void gui_sidebar_draw() {
	gfx_draw_rectangle_filled(0, 0, 150, 720, 0x005c91);
	gfx_draw_rectangle_filled(150, 0, 1280-150, 720, 0);
	gfx_draw_image(splash_screen_logo, 150, 620, 200, 100);
	for (long l = 0; l < menus; l++) {
		font_draw_string(menu_data[l].text, 12, 13 + 20 * l, 0xffffff);
	}

	gfx_draw_rectangle_filled(145, 10 + new_menu * 20, 300, menu_data[new_menu].items * 20, 0x106aff);
	gfx_draw_rectangle_filled(10, 10 + new_menu * 20, 125, 20, 0x0033d7);
	font_draw_string(menu_data[new_menu].text, 12, 13 + 20 * new_menu, 0xffffff);

	for (long l = 0; l < menu_data[new_menu].items; l++) {
		font_draw_string(menu_data[new_menu].item_data[l].text, 152, 13 + 20 * new_menu + 20 * l, 0xffffff);
	}
}

void _gui_sidebar_update() {
	if (new_in_menu != in_menu) {
		if (new_in_menu) {
			gfx_draw_rectangle_filled(150, 10 + current_menu * 20 + new_item * 20, 290, 20, 0x00358e);
			font_draw_string(menu_data[current_menu].item_data[new_item].text, 152, 13 + 20 * current_menu + 20 * new_item, 0xffffff);
		}else{
			gfx_draw_rectangle_filled(150, 10 + current_menu * 20 + current_item * 20, 290, 20, 0x106aff);
			font_draw_string(menu_data[current_menu].item_data[current_item].text, 152, 13 + 20 * current_menu + 20 * current_item, 0xffffff);
		}
	}else if (new_menu == current_menu && new_item != current_item) {
		gfx_draw_rectangle_filled(150, 10 + current_menu * 20 + current_item * 20, 290, 20, 0x106aff);
		font_draw_string(menu_data[current_menu].item_data[current_item].text, 152, 13 + 20 * current_menu + 20 * current_item, 0xffffff);
		gfx_draw_rectangle_filled(150, 10 + current_menu * 20 + new_item * 20, 290, 20, 0x00358e);
		font_draw_string(menu_data[current_menu].item_data[new_item].text, 152, 13 + 20 * current_menu + 20 * new_item, 0xffffff);
	}else if (new_menu != current_menu && new_item == current_item) {
		gfx_draw_rectangle_filled(150, 10 + current_menu * 20, 295, menu_data[current_menu].items * 20, 0);
		gfx_draw_rectangle_filled(145, 10 + current_menu * 20, 5, menu_data[current_menu].items * 20, 0x005c91);
		gfx_draw_rectangle_filled(145, 10 + new_menu * 20, 300, menu_data[new_menu].items * 20, 0x106aff);
		
		gfx_draw_rectangle_filled(10, 10 + current_menu * 20, 125, 20, 0x005c91);
		font_draw_string(menu_data[current_menu].text, 12, 13 + 20 * current_menu, 0xffffff);
		gfx_draw_rectangle_filled(10, 10 + new_menu * 20, 125, 20, 0x0033d7);
		font_draw_string(menu_data[new_menu].text, 12, 13 + 20 * new_menu, 0xffffff);

		for (long l = 0; l < menu_data[new_menu].items; l++) {
			font_draw_string(menu_data[new_menu].item_data[l].text, 152, 13 + 20 * new_menu + 20 * l, 0xffffff);
		}
	}

	current_menu = new_menu;
	current_item = new_item;
	in_menu = new_in_menu;
}

void _gui_sidebar_enter() {
	if (in_menu) {
		gfx_draw_rectangle_filled(700, 0, 1280-700, 720, 0);
		menu_data[current_menu].item_data[current_item].function();
	}
}

void _gui_sidebar_up() {
	if (in_menu) {
		if (current_item == 0) {
			new_item = menu_data[current_menu].items - 1;
		}else{
			new_item = current_item - 1;
		}
	}else{
		if (current_menu == 0) {
			new_menu = menus - 1;
		}else{
			new_menu = current_menu - 1;
		}
	}
	_gui_sidebar_update();
}

void _gui_sidebar_down() {
	if (in_menu) {
		if (current_item + 1 == menu_data[current_menu].items) {
			new_item = 0;
		}else{
			new_item = current_item + 1;
		}
	}else{
		if (current_menu + 1 == menus) {
			new_menu = 0;
		}else{
			new_menu = current_menu + 1;
		}
	}
	_gui_sidebar_update();
}

void _gui_sidebar_left() {
	new_in_menu = false;
	new_item = 0;
	_gui_sidebar_update();
}

void _gui_sidebar_right() {
	new_in_menu = true;
	_gui_sidebar_update();
}

unsigned char toCode(unsigned char c) {
	switch (c) {
		case 10:
		return 'A';
		case 11:
		return 'B';
		case 12:
		return 'C';
		case 13:
		return 'D';
		case 14:
		return 'E';
		case 15:
		return 'F';
		default:
		return c + 48;
	}
}

void print(char c, long y) {
	font_draw_char(toCode((c >> 4) & 0xF), 10, y * 16, 0xffffff);
	font_draw_char(toCode(c & 0xF), 19, y * 16, 0xffffff);
}

unsigned char prev_code = 0;
unsigned char prev_prev_code = 0;

void gui_sidebar_key_pressed(unsigned char keycode) {

	gfx_draw_rectangle_filled(10, 10 * 16, 80, 60, 0x106aff);
	print(prev_prev_code, 10);
	print(prev_code, 11);
	print(keycode, 12);

	if (prev_code == 0xF0) {
		if (prev_prev_code == 0xE0) {
			if (keycode == 0x75) {
				_gui_sidebar_up();
			}else if (keycode == 0x72) {
				_gui_sidebar_down();
			}else if (keycode == 0x6B) {
				_gui_sidebar_left();
			}else if (keycode == 0x74) {
				_gui_sidebar_right();
			}
		}else if (keycode == 0x5A) {
			_gui_sidebar_enter();
		}
	}
	prev_prev_code = prev_code;
	prev_code = keycode;
}