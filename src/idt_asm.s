global idt_load_and_set

idt_load_and_set:
    mov eax, [esp+4]    ; move idt_t to eax
    lidt [eax]          ; load the idt table stored in eax
    ret
