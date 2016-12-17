#ifndef HEADER_PS2
#define HEADER_PS2

#include "ports.h"
#include "asm_utils.h"
#include <stdbool.h>

void ps2_initialize();
bool ps2_has_data();
bool ps2_ready();
unsigned char ps2_read();

#endif