BITS 16

ORG 0x7C00

main:
    mov si, message
    call print_string

    jmp $

print_string:
    mov ah, 0x0
.repeat:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .repeat
.done:
    ret

section .data
    message db "Hello setolyx's server", 0

times 510 - ($ - $$) db 0
dw 0xAA55
