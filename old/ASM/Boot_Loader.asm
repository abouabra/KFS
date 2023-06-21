[org 0x7c00] ; bootloader offset

KERNEL_OFFSET equ 0x1000 ; The same one we used when linking the kernel

; mov bp, 0x9000 ; set the stack
; mov sp, bp


mov [BOOT_DRIVE], dl ; Remember that the BIOS sets us the boot drive in 'dl' on boot
mov bp, 0x9000
mov sp, bp

mov bx, MSG_REAL_MODE 
call print_rm
call print_nl_rm

call load_kernel ; read the kernel from disk
call switch_to_pm

jmp $ ; will never be called

%include "ASM/Print_ASCII.asm"
%include "ASM/Print_HEX.asm"
%include "ASM/Load_Disk.asm"
%include "ASM/32bit-gdt.asm"
%include "ASM/Print_ASCII_32bit.asm"
%include "ASM/32bit-switch.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_rm
    call print_nl_rm

    mov bx, KERNEL_OFFSET ; Read from disk and store in 0x1000
    mov dh, 31
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

BOOT_DRIVE:
    db 0 ; It is a good idea to store it in memory because 'dl' may get overwritten
MSG_LOAD_KERNEL:
    db "Loading kernel into memory", 0

MSG_REAL_MODE:
    db '--------- WE ARE IN REAL MODE -----------', 0

times 510-($-$$) db 0
dw 0xaa55

