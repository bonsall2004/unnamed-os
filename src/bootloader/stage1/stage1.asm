bits 16
org 0x7C00

cli
xor ax, ax
mov ss, ax
mov sp, 0x7C00
sti

mov si, second_stage_msg
call print_string

mov bx, 0x0000
mov dh, 1
mov dl, 0x80

load_stage2:
  mov ah, 0x02
  mov al, 0x01
  mov ch, 0x00
  mov cl, 0x02
  int 0x13
  jc disk_error
  jmp 0x0000:0x8000

disk_error:
  mov si, disk_error_msg
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

second_stage_msg db "Loading Stage2...", 0
disk_error_msg db "Disk Error", 0

times 510-($-$$) db 0
dw 0xAA55

