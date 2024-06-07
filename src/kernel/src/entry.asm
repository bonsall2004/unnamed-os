bits 64

section .init
global start
extern initialize_kernel

start:
  jmp initialize_kernel

section .data
  message db "Kernel Loaded", 0
