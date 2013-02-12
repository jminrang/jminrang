/*
	memory layout
	ld(linker descriptor) provide good layout
	usage option :
		-Map output.txt	==>> System.map

	start address	= 0x1000000 	(kernel_start)
	end address		= 0x1000000 + @ (kernel_end)
	
	PROVIDE : provide kernel source extern value
	usage : refer by extern
		extern const void	kernel_start
		extern const void	kernel_end
		uintptr_t			some_value	= (uintptr_t)&kernel_start;
*/

ENTRY(_start)

SECTIONS
{
    . = 0x100000;
	PROVIDE(kernel_start = ABSOLUTE(.));

    .text : {
        *(multiboot)
        *(.text)
    }
    .data ALIGN(4096) : {
        *(.data)
    }
    .rodata ALIGN(4096) : {
        *(.rodata)
    }
    .bss ALIGN(4096) : {
        *(.bss)
    }
	. = ALIGN(4096);

	PROVIDE(kernel_end = ABSOLUTE(.));
}

