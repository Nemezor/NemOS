#ifndef HEADER_PIC
#define HEADER_PIC

#include "asm_utils.h"
#include <stdbool.h>

void pic_configure_pic(unsigned char master_offset, unsigned char slave_offset);
void pic_send_EOI_normal(unsigned char irq);
void pic_send_EOI_spurious(unsigned char irq);
bool pic_is_normal_IRQ(unsigned char irq);
short pic_read_irr();
short pic_read_isr();
void pic_disable_pic();
short _pic_read_reg(char ocw3);

#endif