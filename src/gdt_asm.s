global gdt_load_and_set

; Load the gdt into the cpu, and enter the kernel segments
gdt_load_and_set:
    mov eax, [esp+4]  ; Fetch gdt_t from parameter stack
    lgdt [eax]        ; Load the gdt table

    ; Reload data segment registers
    mov ax, 0x10 ; 0x10 points at the new data selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Reload CS register containing code selector
    jmp 0x08:.flush ; 0x08 points at the new code selector

.flush:
    ret
