#include "commands.h"
#include "screen.h"
#include "stdbool.h"

#define BUFFER_SIZE 64

char buffer[BUFFER_SIZE];
unsigned int pointer = 0;

bool compare(const char *str) {
	unsigned int i = 0;
	while (str[i] != '\0') {
		if (i >= BUFFER_SIZE) {
			return false;
		}
		if (buffer[i] == '\0') {
			return false;
		}
		if (str[i] != buffer[i]) {
			return false;
		}
		i++;
	}
	if (buffer[i] != '\0') {
		return false;
	}
	return true;
}

void add_to_buffer(char c) {
	buffer[pointer++] = c;
	if (pointer >= BUFFER_SIZE) {
		pointer = 0;
	}
}

void execute_command(void) {
	if (compare(CMD_EXIT) == true) {
		println("ayyy lmao");
		println("...bear");
	}
	for (unsigned int i = 0; i < BUFFER_SIZE; i++) {
		buffer[i] = '\0';
	}
	pointer = 0;
}