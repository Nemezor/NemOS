[BITS 32]

extern pic_send_EOI

%macro irq_service_routine 1
	global __isr_wrappers_irq_%1

	extern isr_irq_%1

	__isr_wrappers_irq_%1:
		pushad
		push esp
		push ebp
		push esi
		push edi
		call isr_irq_%1
		pop edi
		pop esi
		pop ebp
		pop esp
		popad
		iret
%endmacro

%macro err_service_routine 1
	global __isr_wrappers_int_%1

	extern isr_int_%1

	__isr_wrappers_int_%1:
		pushad
		push esp
		push ebp
		push esi
		push edi
		mov eax, [esp - 36]
		push eax
		call isr_int_%1
		add esp, 4
		pop edi
		pop esi
		pop ebp
		pop esp
		popad
		add esp, 4
		iret
%endmacro

%macro int_service_routine 1
	global __isr_wrappers_int_%1

	extern isr_int_%1

	__isr_wrappers_int_%1:
		pushad
		push esp
		push ebp
		push esi
		push edi
		call isr_int_%1
		pop edi
		pop esi
		pop ebp
		pop esp
		popad
		iret
%endmacro

irq_service_routine 0
irq_service_routine 1
irq_service_routine 2
irq_service_routine 3
irq_service_routine 4
irq_service_routine 5
irq_service_routine 6
irq_service_routine 7
irq_service_routine 8
irq_service_routine 9
irq_service_routine 10
irq_service_routine 11
irq_service_routine 12
irq_service_routine 13
irq_service_routine 14
irq_service_routine 15

int_service_routine div_by_zero
int_service_routine debug
int_service_routine NMI
int_service_routine breakpoint
int_service_routine INTO
int_service_routine BOUND
int_service_routine invalid_opcode
int_service_routine co_not_avail
err_service_routine double_fault
int_service_routine co_seg_overrun
err_service_routine TSS_error
err_service_routine seg_not_present
err_service_routine stack_fault
err_service_routine GPF
err_service_routine page_fault
int_service_routine co_error

global __isr_wrappers_int_syscall

extern isr_int_syscall

__isr_wrappers_int_syscall:
	pushad
	push esp
	push ebp
	push esi
	push edi
	push eax
	call isr_int_syscall
	add esp, 4
	pop edi
	pop esi
	pop ebp
	pop esp
	popad
	iret