OUTPUT_ARCH(i386:x86-64)
ENTRY(start)

MEMORY
{
  ram (wxa) : ORIGIN = 0x75000, LENGTH = 0x10000
}

SECTIONS
{
  . = 0x75000;
    .init : { *(.init) }
    .text : { *(.text) }
    .rodata : { *(.rodata) *(.rdata) }
    .data : { *(.data) }
    .bss : { *(.bss) }
    /DISCARD/ : { *(.comment) *(.reloc) *(.edata) *(.idata) *(.xdata) *(.pdata) *(.rsrc) }
}