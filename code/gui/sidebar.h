#ifndef HEADER_GUI_SIDEBAR
#define HEADER_GUI_SIDEBAR

#include "../splash_screen.h"
#include "../gfx.h"
#include "../font.h"
#include "functions.h"
#include <stdbool.h>

void gui_sidebar_draw();
void gui_sidebar_key_pressed(unsigned char keycode);
void _gui_sidebar_up();
void _gui_sidebar_down();
void _gui_sidebar_left();
void _gui_sidebar_right();
void _gui_sidebar_enter();
void _gui_sidebar_update();

#endif