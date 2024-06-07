OUTPUT_ARCH(i386:x86-64)
ENTRY(start)

SECTIONS
{
    . = 0x75000;
    .init : { *(.init) }
    .text : { *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .bss : { *(.bss) }
    /DISCARD/ : { *(.comment) }
}
