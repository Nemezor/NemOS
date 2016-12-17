OUTPUT_FORMAT(elf32-i386)
ENTRY(__start__)
SECTIONS
{
	. = 0x100000;
	.text : {
		*(.text)
	}
	.data : {
		*(.data)
	}
	.bss : {
		*(.bss)
	}
	__lnk_kernel_end = ALIGN(4K);
}
