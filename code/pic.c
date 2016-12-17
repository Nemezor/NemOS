#include "pic.h"

#define PIC1 0x20
#define PIC1_CMD PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2 0xA0
#define PIC2_CMD PIC2
#define PIC2_DATA (PIC2 + 1)

#define PIC_EOI 0x20
#define PIC_READ_IRR 0x0A
#define PIC_READ_ISR 0x0B

#define ICW1_ICW4 0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL 0x08
#define ICW1_INIT 0x10

#define ICW4_8086 0x01
#define ICW4_AUTO 0x02
#define ICW4_BUF_SLAVE 0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM 0x10

void pic_configure_pic(unsigned char master_offset, unsigned char slave_offset) {
	__asm_utils_out8(PIC1_CMD, ICW1_INIT + ICW1_ICW4);
	__asm_utils_io_wait();
	__asm_utils_out8(PIC2_CMD, ICW1_INIT + ICW1_ICW4);
	__asm_utils_io_wait();
	__asm_utils_out8(PIC1_DATA, master_offset);
	__asm_utils_io_wait();
	__asm_utils_out8(PIC2_DATA, slave_offset);
	__asm_utils_io_wait();
	__asm_utils_out8(PIC1_DATA, 4);
	__asm_utils_io_wait();
	__asm_utils_out8(PIC2_DATA, 2);
	__asm_utils_io_wait();

	__asm_utils_out8(PIC1_DATA, ICW4_8086);
	__asm_utils_io_wait();
	__asm_utils_out8(PIC2_DATA, ICW4_8086);
	__asm_utils_io_wait();

	__asm_utils_out8(PIC1_DATA, 0);
	__asm_utils_io_wait();
	__asm_utils_out8(PIC2_DATA, 0);
	__asm_utils_io_wait();
}

bool pic_is_normal_IRQ(unsigned char irq) {
	short isr = pic_read_isr();
	if (irq == 15 && (isr & 0x8000) == 0x8000) {
		return true;
	}else if (irq == 7 && (isr & 0x80) == 0x80) {
		return true;
	}
	return false;
}

void pic_send_EOI_normal(unsigned char irq) {
	if (irq > 7) {
		__asm_utils_out8(PIC2_CMD, PIC_EOI);
	}else{
		__asm_utils_out8(PIC1_CMD, PIC_EOI);
	}
}

void pic_send_EOI_spurious(unsigned char irq) {
	if (irq == 15) {
		__asm_utils_out8(PIC1_CMD, PIC_EOI);
	}
}

short pic_read_isr() {
	return _pic_read_reg(PIC_READ_ISR);
}

short pic_read_irr() {
	return _pic_read_reg(PIC_READ_IRR);
}

void pic_disable_pic() {
	__asm_utils_out8(PIC1_DATA, 0xFF);
	__asm_utils_io_wait();
	__asm_utils_out8(PIC2_DATA, 0xFF);
	__asm_utils_io_wait();
}

short _pic_read_reg(char ocw3) {
	__asm_utils_out8(PIC1_CMD, ocw3);
	__asm_utils_out8(PIC2_CMD, ocw3);
	return ((short)__asm_utils_in8(PIC2_CMD) << 8) || (short)__asm_utils_in8(PIC1_CMD);
}