/* 25 lines, 80 cols - 2 bytes each (char, color) */
#define LINES 25
#define COLUMNS 80
#define BYTES 2
#define SCREENSIZE BYTES * COLUMNS * LINES
#define BASE_COLOR 0x7

extern void write_port(unsigned short port, unsigned char data);

unsigned int current_loc = 0;
char *vidptr = (char*)0xB8000;

void check_positions(void) {
	if (current_loc >= SCREENSIZE) {
		unsigned int line_size = BYTES * COLUMNS;
		current_loc = SCREENSIZE - line_size;
		unsigned int j = 0;
		for (unsigned int i = line_size; i < SCREENSIZE; i++) {
			vidptr[j++] = vidptr[i];
		}
		while (j < SCREENSIZE) {
			vidptr[j++] = ' ';
			vidptr[j++] = BASE_COLOR;
		}
	}
    write_port(0x3D4, 0x0F);
    write_port(0x3D5, (unsigned char)(current_loc / 2 & 0xFF));
    write_port(0x3D4, 0x0E);
    write_port(0x3D5, (unsigned char )((current_loc / 2 >> 8) & 0xFF));
}

void clear(void) {
	for (unsigned int i = 0; i < SCREENSIZE; i++) {
		vidptr[i++] = ' ';
		vidptr[i] = BASE_COLOR;
	}
	current_loc = 0;
	check_positions();
}

void println_newline() {
	unsigned int line_size = BYTES * COLUMNS;
	current_loc += line_size - current_loc % line_size;
	check_positions();
}

void print_char_colored(char c, char color) {
	if (c == '\n') {
		println_newline();
	}else if (c == '\b') {
		if (current_loc <= 0) {
			current_loc = 0;
			return;
		}
		current_loc--;
		vidptr[current_loc--] = BASE_COLOR;
		vidptr[current_loc] = ' ';
	}else{
		vidptr[current_loc++] = c;
		vidptr[current_loc++] = color;
	}
	check_positions();
}

void print_char(char c) {
	print_char_colored(c, BASE_COLOR);
}

void print_colored(const char *str, char color) {
	unsigned int i = 0;
	while (str[i] != '\0') {
		print_char_colored(str[i++], color);
	}
}

void print(const char *str) {
	print_colored(str, BASE_COLOR);
}

void println_colored(const char *str, char color) {
	print_colored(str, color);
	println_newline();
}

void println(const char *str) {
	println_colored(str, BASE_COLOR);
}