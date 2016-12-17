#include "setup.h"

char* scratch_memory;

void __setup_kernel_entry(multiboot_info_t* mbinfo, long bootloader_return, long mem) {
	if (bootloader_return != MULTIBOOT_BOOTLOADER_MAGIC) {
		__asm_utils_hang();
	}
	scratch_memory = (char*)mem;
	video_read_from_bootloader(mbinfo, scratch_memory);
	memory_read_from_bootloader(mbinfo, scratch_memory);
	gdt_setup_global_descriptor_table();
	idt_setup_interrupt_descriptor_table();
	ps2_initialize();
	cpuid_detect();

	gui_sidebar_draw();

	__asm_utils_spinlock();

	__asm_utils_stop();
}