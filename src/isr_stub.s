; Expose to C code
extern isr_handler
extern irq_handler

; Define the template function for an ISR with no code error
%macro ISR_NO_ERR 1
    global isr%1
    isr%1:
        cli
        push    byte 0    ; dummy error code
        push    byte %1   ; interrupt number
        jmp     isr_stub
%endmacro

; Define the template function for an ISR with a code error
%macro ISR_ERR 1
    global isr%1
    isr%1:
        cli
        push    byte %1   ; interrupt number
        jmp     isr_stub
%endmacro

; Define the template function for an IRQ
%macro IRQ 2
    global irq%1
    irq%1:
        cli
        push    byte 0    ; dummy error code
        push    byte %2   ; irq number
        jmp     irq_stub
%endmacro

ISR_NO_ERR 0  ; Division By Zero Exception
ISR_NO_ERR 1  ; Debug Exception
ISR_NO_ERR 2  ; Non Maskable Interrupt Exception
ISR_NO_ERR 3  ; Breakpoint Exception
ISR_NO_ERR 4  ; Into Detected Overflow Exception
ISR_NO_ERR 5  ; Out of Bounds Exception
ISR_NO_ERR 6  ; Invalid Opcode Exception
ISR_NO_ERR 7  ; No Coprocessor Exception
ISR_ERR    8  ; Double Fault Exception
ISR_NO_ERR 9  ; Coprocessor Segment Overrun Exception
ISR_ERR    10 ; Bad TSS Exception
ISR_ERR    11 ; Segment Not Present Exception
ISR_ERR    12 ; Stack Fault Exception
ISR_ERR    13 ; General Protection Fault Exception
ISR_ERR    14 ; Page Fault Exception
ISR_NO_ERR 15 ; Unknown Interrupt Exception
ISR_NO_ERR 16 ; Coprocessor Fault Exception
ISR_NO_ERR 17 ; Alignment Check Exception (486+)
ISR_NO_ERR 18 ; Machine Check Exception (Pentium/586+)
ISR_NO_ERR 19 ; Reserved Exceptions
ISR_NO_ERR 20 ; ...
ISR_NO_ERR 21 ; ...
ISR_NO_ERR 22 ; ...
ISR_NO_ERR 23 ; ...
ISR_NO_ERR 24 ; ...
ISR_NO_ERR 25 ; ...
ISR_NO_ERR 26 ; ...
ISR_NO_ERR 27 ; ...
ISR_NO_ERR 28 ; ...
ISR_NO_ERR 29 ; ...
ISR_NO_ERR 30 ; ...
ISR_NO_ERR 31 ; ...

IRQ 0,  32 ; Programmable Interrupt Timer Interrupt
IRQ 1,  33 ; Keyboard Interrupt
IRQ 2,  34 ; Cascade (used internally by the two PICs. never raised)
IRQ 3,  35 ; COM2 (if enabled)
IRQ 4,  36 ; COM1 (if enabled)
IRQ 5,  37 ; LPT2 (if enabled)
IRQ 6,  38 ; Floppy Disk
IRQ 7,  39 ; LPT1 / Unreliable "spurious" interrupt (usually)
IRQ 8,  40 ; CMOS real-time clock (if enabled)
IRQ 9,  41 ; Free for peripherals / legacy SCSI / NIC
IRQ 10, 42 ; Free for peripherals / SCSI / NIC
IRQ 11, 43 ; Free for peripherals / SCSI / NIC
IRQ 12, 44 ; PS2 Mouse
IRQ 13, 45 ; FPU / Coprocessor / Inter-processor
IRQ 14, 46 ; Primary ATA Hard Disk
IRQ 15, 47 ; Secondary ATA Hard Disk

; The ISR stub
; It saves the processor state, sets up for kernel mode segments,
; calls the C-level isr handler, and finally restores the stack frame
isr_stub:
    pusha          ; pushes edi, esi, ebp, esp, ebx, edx, ecx, eax

    mov ax, ds
    push eax

    mov ax, 0x10   ; load kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop eax        ; load original data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8     ; cleans pushed error code and ISR number
    sti

    iret           ; pops cs, eip, eflags, ss, esp

; The IRQ stub
; Same as ISR stub but calls the C-level irq handler instead
irq_stub:
    pusha          ; pushes edi, esi, ebp, esp, ebx, edx, ecx, eax

    mov ax, ds
    push eax

    mov ax, 0x10   ; load kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop eax        ; load original data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8     ; cleans pushed error code and ISR number
    sti

    iret           ; pops cs, eip, eflags, ss, esp
