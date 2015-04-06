bits 32
section .text
	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002 + 0x00)

global start
start:
	mov esp, _sys_stack
	extern kernel_main
	call kernel_main

SECTION .bss
	resb 8192				; give 8kb stack space
_sys_stack: