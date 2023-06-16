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


mov bp, 0x8000 ; set the base to hight point
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


call print_nl ;

mov bx, text
call print

call print_nl

mov dx, 0x0123
call print_hex
call print_nl

mov dx, 0xABCD
call print_hex
call print_nl
call print_nl

mov dx, 0x0
mov bp, 0x8000 ; set the base to hight point
mov sp, bp

mov bx, 0x9000 ; es:bx = 0x0000:0x9000 = 0x09000
mov dh, 2 ; read 2 sectors

call disk_load

mov dx, [0x9000] ; retrieve the first loaded word,
call print_hex

call print_nl

mov dx, [0x9000 + 512] ; first word from second loaded sector
call print_hex

loop:
    jmp loop

; %include "Print_ASCII.asm"
; %include "Print_HEX.asm"
%include "Load_Disk.asm"


data_in_adress:
    db "X"

text:
    db '--- My Name is Ayman ----', 0

times 510-($-$$) db 0
dw 0xaa55

times 256 dw 0x1a2b ; sector 2 = 512 bytes
times 256 dw 0xface ; sector 3 = 512 bytes
