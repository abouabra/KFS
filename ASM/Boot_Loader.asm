[org 0x7c00] ; bootloader offset

mov bp, 0x9000 ; set the stack
mov sp, bp

mov bx, MSG_REAL_MODE
call print_rm ; This will be written after the BIOS messages
call print_nl_rm

call switch_to_pm

loop:
    jmp loop

%include "ASM/Print_ASCII.asm"
%include "ASM/Print_HEX.asm"
%include "ASM/32bit-switch.asm"
; %include "32bit-gdt.asm"
; %include "Load_Disk.asm"


[bits 32]

mov ebx, MSG_PROTECTED_MODE
call print_pm ; Note that this will be written at the top left corner
jmp $


MSG_PROTECTED_MODE:
    db '--------- WE ARE IN PROTECTED MODE -----------', 0

MSG_REAL_MODE:
    db '--------- WE ARE IN REAL MODE -----------', 0

times 510-($-$$) db 0
dw 0xaa55
