OUTPUT_FORMAT(binary)
OUTPUT_ARCH(x86_64)
ENTRY(start)

SECTIONS
{
    . = 0x100000;
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
    /DISCARD/ : { *(.comment) }
}
