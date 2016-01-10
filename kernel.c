#include "keyboard.h"
#include "screen.h"
#include "idt.h"

#define LOGO_OS_COLOR 0xB
#define LOGO_NEM_COLOR 0xF

void main(void) {
	clear();
	println_newline();
	print_colored("     _   _                ", LOGO_NEM_COLOR);
	println_colored(" ____   _____", LOGO_OS_COLOR);
	print_colored("    | \\ | |               ", LOGO_NEM_COLOR);
	println_colored("/ __ \\ / ____|", LOGO_OS_COLOR);
	print_colored("    |  \\| | ___ _ __ ___ ", LOGO_NEM_COLOR);
	println_colored("| |  | | (___  ", LOGO_OS_COLOR);
	print_colored("    | . ` |/ _ \\ '_ ` _ \\", LOGO_NEM_COLOR);
	println_colored("| |  | |\\___ \\ ", LOGO_OS_COLOR);
	print_colored("    | |\\  |  __/ | | | | ", LOGO_NEM_COLOR);
	println_colored("| |__| |____) |", LOGO_OS_COLOR);
	print_colored("    |_| \\_|\\___|_| |_| |_|", LOGO_NEM_COLOR);
	println_colored("\\____/|_____/ ", LOGO_OS_COLOR);
	println_newline();

	initialize_idt();
	initialize_keyboard();

	while (1);
}
