section .text

isr0:
  ret
isr1:
  pusha
  mov eax, 0x60
  in al, eax
  mov al, 0x20
  out 0x20, al

  popa
  iretq

section .data
globle idt
idt:
  dw isr0
  dw 0x08
  db 0
  db 0x8E
  dw isr0 >> 16

  dw irs1
  dw  0x08
  db 0
  db 0x8E
  dw isr1 >> 16
