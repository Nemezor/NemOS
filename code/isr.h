#ifndef HEADER_ISR
#define HEADER_ISR

#include "pic.h"
#include "ps2.h"
#include "gfx.h"
#include <stdbool.h>

#include "gui/sidebar.h"

void isr_irq_0();
void isr_irq_1();
void isr_irq_2();
void isr_irq_3();
void isr_irq_4();
void isr_irq_5();
void isr_irq_6();
void isr_irq_7();
void isr_irq_8();
void isr_irq_9();
void isr_irq_10();
void isr_irq_11();
void isr_irq_12();
void isr_irq_13();
void isr_irq_14();
void isr_irq_15();

void isr_int_div_by_zero();
void isr_int_debug();
void isr_int_NMI();
void isr_int_breakpoint();
void isr_int_INTO();
void isr_int_BOUND();
void isr_int_invalid_opcode();
void isr_int_co_not_avail();
void isr_int_double_fault(long error_code);
void isr_int_co_seg_overrun();
void isr_int_TSS_error(long error_code);
void isr_int_seg_not_present(long error_code);
void isr_int_stack_fault(long error_code);
void isr_int_GPF(long error_code);
void isr_int_page_fault(long error_code);
void isr_int_co_error();

void isr_int_syscall(long code);

#endif