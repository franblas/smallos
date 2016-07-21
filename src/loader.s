global loader                  ; The entry symbol for ELF
extern kmain

MAGIC_NUMBER equ 0x1BADB002    ; Define the magic number constant
FLAGS        equ 0x0           ; Multiboot flags
CHECKSUM     equ -MAGIC_NUMBER ; Calculate the checksum (magic number + checksum should equal 0)

KERNEL_STACK_SIZE equ 0x1000   ; Size of stack in bytes (4k)

section .bss
align 4                        ; Align at 4 bytes
kernel_stack:                  ; Label points to beginning of memory
    resb KERNEL_STACK_SIZE     ; Reserve stack for the kernel

section .text                  ; Start of the text (code) section
align 4                        ; The code must be 4 byte aligned
    dd MAGIC_NUMBER            ; Write the magic number to the machine code
    dd FLAGS                   ; the flags,
    dd CHECKSUM                ; and the checksum

loader:                                         ; The loader label (defined as entry point in linker script)
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ; Point esp to the start of the stack (end of memory area)
    cli ; Clear interrupt flag (we set it up again later in the kmain with sti flag)
    call kmain

.loop:
    jmp .loop                  ; Loop forever
