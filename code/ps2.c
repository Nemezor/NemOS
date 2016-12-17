#include "ps2.h"

bool dual_channel = false;

void ps2_initialize() {
	// TODO dont assume PS2 exists

	// disable devices
	__asm_utils_out8(PORTS_PS2_CMD, 0xAD);
	__asm_utils_out8(PORTS_PS2_CMD, 0xA7);

	// flush buffer
	__asm_utils_in8(PORTS_PS2_DATA);

	// change config byte
	__asm_utils_out8(PORTS_PS2_CMD, 0x20);
	char config = __asm_utils_in8(PORTS_PS2_DATA);
	config &= 0xBC;
	dual_channel = (config & 0x20) == 0x20;
	__asm_utils_out8(PORTS_PS2_CMD, 0x60);
	while (!ps2_ready());
	__asm_utils_out8(PORTS_PS2_DATA, config);

	// controller self-test
	__asm_utils_out8(PORTS_PS2_CMD, 0xAA);
	while (!ps2_has_data());
	char reply = __asm_utils_in8(PORTS_PS2_DATA);
	if (reply != 0x55) {
		// self-test failed
		__asm_utils_hang();
		return;
	}

	// test first PS/2 port
	__asm_utils_out8(PORTS_PS2_CMD, 0xAB);
	while (!ps2_has_data());
	reply = __asm_utils_in8(PORTS_PS2_DATA);
	if (reply != 0) {
		// port is borken
		__asm_utils_hang();
		return;
	}

	// enable IRQs for first PS/2 port
	__asm_utils_out8(PORTS_PS2_CMD, 0x20);
	config = __asm_utils_in8(PORTS_PS2_DATA);
	config |= 1;
	__asm_utils_out8(PORTS_PS2_CMD, 0x60);
	while (!ps2_ready());
	__asm_utils_out8(PORTS_PS2_DATA, config);

	// enable first PS/2 port
	__asm_utils_out8(PORTS_PS2_CMD, 0xAE);
}

bool ps2_has_data() {
	char status = __asm_utils_in8(PORTS_PS2_CMD);
	return (status & 1) == 1;
}

bool ps2_ready() {
	char status = __asm_utils_in8(PORTS_PS2_CMD);
	return (status & 2) != 2;
}

unsigned char ps2_read() {
	return __asm_utils_in8(PORTS_PS2_DATA);
}