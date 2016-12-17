#include "idt.h"

long long* IDT;

void idt_setup_interrupt_descriptor_table() {
	IDT = (long long*)memory_kalloc(256 * sizeof(long long));

	for (unsigned long l = 0; l < 256 * sizeof(long long); l++) {
		IDT[l] = 0;
	}

	// exceptions
	IDT[0] = idt_create_descriptor_entry(&__isr_wrappers_int_div_by_zero);
	IDT[1] = idt_create_descriptor_entry(&__isr_wrappers_int_debug);
	IDT[2] = idt_create_descriptor_entry(&__isr_wrappers_int_NMI);
	IDT[3] = idt_create_descriptor_entry(&__isr_wrappers_int_breakpoint);
	IDT[4] = idt_create_descriptor_entry(&__isr_wrappers_int_INTO);
	IDT[5] = idt_create_descriptor_entry(&__isr_wrappers_int_BOUND);
	IDT[6] = idt_create_descriptor_entry(&__isr_wrappers_int_invalid_opcode);
	IDT[7] = idt_create_descriptor_entry(&__isr_wrappers_int_co_not_avail);
	IDT[8] = idt_create_descriptor_entry(&__isr_wrappers_int_double_fault);
	IDT[9] = idt_create_descriptor_entry(&__isr_wrappers_int_co_seg_overrun);
	IDT[10] = idt_create_descriptor_entry(&__isr_wrappers_int_TSS_error);
	IDT[11] = idt_create_descriptor_entry(&__isr_wrappers_int_seg_not_present);
	IDT[12] = idt_create_descriptor_entry(&__isr_wrappers_int_stack_fault);
	IDT[13] = idt_create_descriptor_entry(&__isr_wrappers_int_GPF);
	IDT[14] = idt_create_descriptor_entry(&__isr_wrappers_int_page_fault);
	IDT[16] = idt_create_descriptor_entry(&__isr_wrappers_int_co_error);
	
	// IRQs
	IDT[32] = idt_create_descriptor_entry(&__isr_wrappers_irq_0);
	IDT[33] = idt_create_descriptor_entry(&__isr_wrappers_irq_1);
	IDT[34] = idt_create_descriptor_entry(&__isr_wrappers_irq_2);
	IDT[35] = idt_create_descriptor_entry(&__isr_wrappers_irq_3);
	IDT[36] = idt_create_descriptor_entry(&__isr_wrappers_irq_4);
	IDT[37] = idt_create_descriptor_entry(&__isr_wrappers_irq_5);
	IDT[38] = idt_create_descriptor_entry(&__isr_wrappers_irq_6);
	IDT[39] = idt_create_descriptor_entry(&__isr_wrappers_irq_7);
	IDT[40] = idt_create_descriptor_entry(&__isr_wrappers_irq_8);
	IDT[41] = idt_create_descriptor_entry(&__isr_wrappers_irq_9);
	IDT[42] = idt_create_descriptor_entry(&__isr_wrappers_irq_10);
	IDT[43] = idt_create_descriptor_entry(&__isr_wrappers_irq_11);
	IDT[44] = idt_create_descriptor_entry(&__isr_wrappers_irq_12);
	IDT[45] = idt_create_descriptor_entry(&__isr_wrappers_irq_13);
	IDT[46] = idt_create_descriptor_entry(&__isr_wrappers_irq_14);
	IDT[47] = idt_create_descriptor_entry(&__isr_wrappers_irq_15);

	// software interrupts
	IDT[0x80] = idt_create_descriptor_entry(&__isr_wrappers_int_syscall);

	pic_configure_pic(32, 40);
	__asm_utils_load_idt((long)IDT, 256 * sizeof(long long) - 1);
	__asm_utils_sti();
}

long long idt_create_descriptor_entry(void (*function)(void)) {
	long long entry = 0;

	entry |= 0xE << 8; // 32 bit interrupt gate
	entry |= 1 << 15; // present
	entry |= (unsigned long)function & 0xFFFF0000;

	entry <<= 32;

	entry |= (unsigned long)function & 0xFFFF;
	entry |= 0x8 << 16; // GDT code selector

	return entry;
}