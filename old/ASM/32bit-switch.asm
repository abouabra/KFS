; %include "ASM/header.asm"
; %include "ASM/32bit-gdt.asm"
; %include "ASM/Print_ASCII_32bit.asm"

KERNEL_OFFSET equ 0x1000 ; The same one we used when linking the kernel

[bits 16]
switch_to_pm:
    cli ; 1. disable interrupts
    lgdt [gdt_descriptor] ; 2. load the GDT descriptor
    
    mov eax, cr0
    or eax, 0x1 ; 3. set 32-bit mode bit in cr0
    mov cr0, eax
    
    jmp CODE_SEG:init_pm ; 4. far jump by using a different segment

[bits 32]
init_pm:
    mov ax, DATA_SEG ; 5. update the segment registers 
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; 6. update the stack right at the top of the free space
    mov esp, ebp
    call BEGIN_PM ; 7. Call a well-known label with useful code

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROTECTED_MODE
    call print_pm ; Note that this will be written at the top left corner
    call KERNEL_OFFSET ; Give control to the kernel
    jmp $


MSG_PROTECTED_MODE:
    db '--------- WE ARE IN PROTECTED MODE -----------', 0
