bits 16
org 0x8000

start:
  cli
  call check_cpuid
  call check_long_mode_compatibility
  call enter_long_mode





; -------------------------------------------------------
check_cpuid:
  pushfd
  pop eax

  mov ecx, eax

  xor eax, 1 << 21

  push eax
  popfd

  pushfd
  pop eax

  push ecx
  popfd

  xor eax, ecx
  jz .NoCPUID
  ret

  .NoCPUID:
    mov si, cpuid_failed_err
    call error
; -------------------------------------------------------
check_long_mode_compatibility:
  mov eax, 0x80000000
  cpuid
  cmp eax, 0x80000001
  jb .NoLongMode

  mov eax, 0x80000001
  cpuid
  test edx, 1 << 29
  jz .NoLongMode
  ret

  .NoLongMode:
    mov si, long_mode_unsupported_err
    call error
; -------------------------------------------------------
enter_long_mode:
  mov eax, cr0
  and eax, 01111111111111111111111111111111b
  mov cr0, eax

  xor ax, ax
  mov es, ax

  mov edi, 0x1000
  mov cr3, edi
  xor eax, eax
  mov ecx, 4096
  rep stosd
  mov edi, cr3


  mov dword [edi], 0x2003
  add edi, 0x1000
  mov dword [edi], 0x3003
  add edi, 0x1000
  mov dword [edi], 0x4003
  add edi, 0x1000

  mov ebx, 0x00000003
  mov ecx, 512

  .set_entry:
    mov dword [edi], ebx
    add edi, 8
    add ebx, 0x1000
    loop .set_entry



  call check_pae_paging

  mov ecx, 0xC0000080
  rdmsr
  or eax, 1 << 8
  wrmsr

  mov eax, cr0
  or eax, 1 << 31 | 1 << 0
  mov cr0, eax



  lgdt [gdt_descriptor]



  jmp 0x08:long_mode_entry

; -------------------------------------------------------
check_pae_paging:
  mov eax, cr4
  or eax, 1 << 5
  mov cr4, eax
  ret
; -------------------------------------------------------
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
; -------------------------------------------------------
error:
  call print_string
  hlt

  .err_loop:
    jmp .err_loop
; -------------------------------------------------------


gdt_start:
  gdt_null:
      dq 0
  gdt_code:
      dq 0x00af9b000000ffff
  gdt_data:
      dq 0x00af93000000ffff
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

[bits 64]
long_mode_entry:
  jmp 0x75000

cpuid_failed_err db "CPUID not supported", 0
long_mode_unsupported_err db "Long Mode not supported", 0
happy_message db "Boom babyyy.", 0

times 512-($-$$) db 0