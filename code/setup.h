#ifndef HEADER_SETUP
#define HEADER_SETUP

#include "multiboot.h"
#include "memory.h"
#include "asm_utils.h"
#include "video.h"
#include "gdt.h"
#include "idt.h"
#include "ps2.h"
#include "cpuid.h"
#include "gui/sidebar.h"
#include <stdint.h>

extern unsigned long __lnk_kernel_end;

void __setup_kernel_entry(multiboot_info_t* mbinfo, long bootloader_return, long mem);

#endif