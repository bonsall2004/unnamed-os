bits 16
org 0x8000

start:
  mov ax, 0x4F02  ; VESA Set Super VGA Mode
  mov bx, 0x118   
  int 0x10 
  cli
  lgdt [gdt_descriptor]
  mov eax, cr0
  or eax, 1
  mov cr0, eax

  mov eax, cr4
  or eax, 0x20
  or eax, 0x20
  mov cr4, eax

  mov eax, 0x9C002
  mov cr3, eax

  mov eax, cr0
  or eax, 0x80000000
  mov cr0, eax

  mov ecx, 0xC0000080
  rdmsr
  or eax, 1 << 8
  wrmsr

  jmp 0x08:long_mode_entry

gdt_start:
gdt_null:
    dq 0x0000000000000000
gdt_code:
    dq 0x00af9b000000ffff
gdt_data:
    dq 0x00af93000000ffff
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start
bits 32
long_mode_entry:
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  jmp 0x08:0x75000

bits 64



kernel_entry:
  jmp 0x75000


times 512-($-$$) db 0

