bits 32
section .text
	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002 + 0x00)

extern kernel_main

global start
start:
	cli 					; ignore interrupts
	mov esp, _sys_stack		; set stack pointer
	call kernel_main		; start our kernel
	hlt 					; halt CPU

SECTION .bss
	resb 8192				; give 8kb stack space
_sys_stack: