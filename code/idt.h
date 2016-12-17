#ifndef HEADER_IDT
#define HEADER_IDT

#include "memory.h"
#include "asm_utils.h"
#include "pic.h"
#include "isr_wrappers.h"

void idt_setup_interrupt_descriptor_table();
long long idt_create_descriptor_entry(void (*function)(void));

#endif