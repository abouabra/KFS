[bits 32]

VIDEO_MEMORY equ 0xb8000
COLOR equ 0x02

; 0x0 - Black
; 0x1 - Blue
; 0x2 - Green
; 0x3 - Cyan
; 0x4 - Red
; 0x5 - Magenta
; 0x6 - Brown
; 0x7 - Light gray
; 0x8 - Dark gray
; 0x9 - Light blue
; 0xA - Light green
; 0xB - Light cyan
; 0xC - Light red
; 0xD - Light magenta
; 0xE - Yellow
; 0xF - White

print_pm:
	pusha
	mov edx, VIDEO_MEMORY

print_pm_loop:
	mov al, [ebx]
	mov ah, COLOR
	cmp al, 0
	je print_pm_done
	mov [edx], ax
	add ebx, 1
	add edx, 2
	jmp print_pm_loop

print_pm_done:
	popa
	ret