[org 0x7c00]
mov ah, 0x0e ; switch to TTY mode
mov al, 'M'
int 0x10

mov al, 'i'
int 0x10

mov al, 'n'
int 0x10

mov al, 'i'
int 0x10

mov al, ' '
int 0x10

mov al, 'O'
int 0x10

mov al, 'S'
int 0x10

mov al, [data_in_adress]
int 0x10

mov al, ' '
int 0x10


mov bp, 0x8000
mov sp, bp

push 'I'
push 'J'
push 'K'

pop bx
mov al, bl
int 0x10

pop bx
mov al, bl
int 0x10

pop bx
mov al, bl
int 0x10

loop:
    jmp loop

data_in_adress:
    db "X"

times 510-($-$$) db 0
dw 0xaa55