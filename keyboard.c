#include "keylayout_cz.h"
#include "screen.h"
#include "command.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

extern unsigned char keyboard_map[128];
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);

void initialize_keyboard(void) {
	write_port(0x21 , 0xFD);
}

void keyboard_handler_main(void) {
	unsigned char status;
	char keycode;

	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);
		if(keycode < 0) {
			return;
		}
		char c = keyboard_map[keycode];
		print_char(c);
		if (c == '\n') {
			execute_command();
		}else{
			add_to_buffer(c);
		}
	}
}