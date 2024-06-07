bits 64

section .text
    global _start

_start:
    mov rsi, message
    call print_string

    ; Your kernel code goes here

    hlt

print_string:
    mov rdi, rsi            ; Load address of the message into RDI
.loop:
    lodsb                   ; Load the next byte from the string into AL
    test al, al             ; Check if AL is zero (end of string)
    jz .done                ; If AL is zero, jump to the end
    mov ah, 0x0E            ; Set AH = 0x0E for the function to print a character
    mov ebx, 0x0F00         ; Set BL = 0x0F to display the character in white on black background
    int 0x10                ; Call BIOS interrupt to print the character
    jmp .loop               ; Repeat until end of string
.done:
    ret                     ; Return from the function

section .data
    message db "Kernel Loaded", 0
