#include "isr.h"

////// IRQs

void isr_irq_0() {
	pic_send_EOI_normal(0);
}

	// kbd interrupt
void isr_irq_1() {
	unsigned char data = ps2_read();

	gui_sidebar_key_pressed(data);

	pic_send_EOI_normal(1);
}

void isr_irq_2() {
	pic_send_EOI_normal(2);
}

void isr_irq_3() {
	pic_send_EOI_normal(3);
}

void isr_irq_4() {
	pic_send_EOI_normal(4);
}

void isr_irq_5() {
	pic_send_EOI_normal(5);
}

void isr_irq_6() {
	pic_send_EOI_normal(6);
}

void isr_irq_7() {
	if (pic_is_normal_IRQ(7)) {
		pic_send_EOI_normal(7);
	}
}

void isr_irq_8() {
	pic_send_EOI_normal(8);
}

void isr_irq_9() {
	pic_send_EOI_normal(9);
}

void isr_irq_10() {
	pic_send_EOI_normal(10);
}

void isr_irq_11() {
	pic_send_EOI_normal(11);
}

void isr_irq_12() {
	pic_send_EOI_normal(12);
}

void isr_irq_13() {
	pic_send_EOI_normal(13);
}

void isr_irq_14() {
	pic_send_EOI_normal(14);
}

void isr_irq_15() {
	if (pic_is_normal_IRQ(15)) {
		pic_send_EOI_normal(15);
	}else{
		pic_send_EOI_spurious(15);
	}
}

////// exceptions

void isr_int_div_by_zero() {

}

void isr_int_debug() {

}

void isr_int_NMI() {

}

void isr_int_breakpoint() {

}

void isr_int_INTO() {

}

void isr_int_BOUND() {

}

void isr_int_invalid_opcode() {

}

void isr_int_co_not_avail() {

}

void isr_int_double_fault(long error_code) {

}

void isr_int_co_seg_overrun() {

}

void isr_int_TSS_error(long error_code) {

}

void isr_int_seg_not_present(long error_code) {

}

void isr_int_stack_fault(long error_code) {

}

void isr_int_GPF(long error_code) {

}

void isr_int_page_fault(long error_code) {

}

void isr_int_co_error() {

}

////// software interrupts

void isr_int_syscall(long code) {

}