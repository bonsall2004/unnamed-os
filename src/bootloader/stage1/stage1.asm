bits 16
org 0x7C00

start:
  cli
  xor ax, ax
  mov ss, ax
  mov sp, 0x7C00
  sti

  mov si, loading_msg
  call print_string

  call read_e820

  mov bx, 0x0000
  mov dh, 1
  mov dl, 0x80

  jmp load_stage2

read_e820:
  mov ax, 0x7000
  mov es, ax
  mov di, 8
  xor ebx, ebx

.loop:
  inc dword es:[0]
  mov dword  es:[di+20], 1

  mov eax, 0xE820
  mov edx, 0x534D4150
  mov ecx, 24
  int 0x15
  jc mem_map_failed

  add edi, 24
  test ebx, ebx
  jnz .loop

  dec dword  es:[0]
  ret

load_stage2:
  mov ax, 0x800
  mov es, ax
  xor bx, bx

  mov ah, 0x02 ; BIOS function read sectors
  mov al, 0x01 ; Sectors to read
  mov ch, 0x00 ; Cylinder
  mov cl, 0x02 ; Starting sector number of stage 2 on disk
  mov dh, 0x00 ; Head number
  mov dl, 0x80 ; Drive number (0x80 is the first)

  int 0x13
  jc disk_error

  mov ax, 0x7500
  mov es, ax
  xor bx, bx
  mov ah, 0x02 ; BIOS function read sectors
  mov al, 0x3F ; Sectors to read
  mov ch, 0x00 ; Cylinder
  mov cl, 0x03 ; Starting sector number of stage 2 on disk
  mov dh, 0x00 ; Head number
  mov dl, 0x80 ; Drive number (0x80 is the first)

  int 0x13
  jc disk_error

  mov si, loaded_msg
  call print_string

  jmp 0x0000:0x8000

disk_error:
  mov si, disk_error_msg
  call print_string
  hlt
mem_map_failed:
  mov si, mem_map_failed_msg
  call print_string
  hlt

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

loading_msg db "Loading Stage2...", 0
loaded_msg db "Loaded Stage2!!", 0
disk_error_msg db "Disk Error", 0
mem_map_failed_msg db "Memory Mapping Failed!", 0

times 510-($-$$) db 0
dw 0xAA55
