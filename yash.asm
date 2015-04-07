[BITS 32]
ALIGN 4
mboot:
	MULTIBOOT_PAGE_ALIGN	equ 1 << 0
	MULTIBOOT_MEMORY_INFO	equ 1 << 1
	MULTIBOOT_AOUT_KLUDGE	equ 1 << 16
	MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
	MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
	MULTIBOOT_CHECKSUM		equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
	EXTERN code, bss, end
	; grub header and boot sig
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_CHECKSUM
	; linker does these:
	dd mboot
	dd code
	dd bss
	dd end
	dd start

global start
start:
	mov esp, _sys_stack
	jmp yash

global gdt_flush
extern gp
gdt_flush:
	lgdt[gp]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2
flush2:
	ret

global yash
yash:
	extern kernel_main
	call kernel_main
	jmp $

SECTION .bss
	resb 8192				; give 8kb stack space
_sys_stack: