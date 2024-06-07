bits 16
org 0x8000

start:
    cli
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:protected_mode_entry

bits 32
protected_mode_entry:

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov eax, cr4
    or eax, 0x20
    mov cr4, eax

    mov eax, 0x9C002
    mov cr3, eax

    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    jmp 0x08:long_mode_entry

bits 64
long_mode_entry:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

print_string:
    mov ah, 0x0E
    .loop:
        lodsb
        or al, al
        jz .done
        int 0x10
        jmp .loop
    .done:
        ret

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

disk_error_msg db "Disk Error", 0

times 512-($-$$) db 0
