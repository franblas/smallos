#include "idt.h"
#include "isr.h"
#include "irq.h"

#define IDT_ENTRY_FLAGS 0x8E
#define IDT_ENTRY_SEL 0x08

#define IDT_NUM_ENTRIES 256

/* Global */
idt_table idt_t; // idt table
idt_entry idt_entries[IDT_NUM_ENTRIES]; // idt entries

/* IDT functions */
void idt_create_entry(u32 n, u32 base, u16 selector, u8 flags)
{
  idt_entries[n].base_low = base & 0xFFFF;
  idt_entries[n].selector = selector;
  idt_entries[n].reserved = 0;
  idt_entries[n].flags = flags;
  idt_entries[n].base_high = (base >> 16) & 0xFFFF;
}

void idt_init()
{
  // initialize idt table
  idt_t.size = (sizeof (idt_entry) * IDT_NUM_ENTRIES) - 1;
  idt_t.address = (u32)&idt_entries;

  // Remap irq through PIC chip before init
  irq_remap();

  // initialize idt entries
  // ISR (Interrupt service routines)
  idt_create_entry(0, (u32)isr0, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(1, (u32)isr1, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(2, (u32)isr2, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(3, (u32)isr3, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(4, (u32)isr4, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(5, (u32)isr5, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(6, (u32)isr6, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(7, (u32)isr7, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(8, (u32)isr8, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(9, (u32)isr9, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(10, (u32)isr10, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(11, (u32)isr11, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(12, (u32)isr12, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(13, (u32)isr13, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(14, (u32)isr14, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(15, (u32)isr15, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(16, (u32)isr16, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(17, (u32)isr17, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(18, (u32)isr18, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(19, (u32)isr19, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(20, (u32)isr20, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(21, (u32)isr21, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(22, (u32)isr22, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(23, (u32)isr23, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(24, (u32)isr24, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(25, (u32)isr25, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(26, (u32)isr26, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(27, (u32)isr27, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(28, (u32)isr28, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(29, (u32)isr29, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(30, (u32)isr30, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(31, (u32)isr31, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);

  // IRQ (Interrupt requests)
  idt_create_entry(32, (u32)irq0, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(33, (u32)irq1, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(34, (u32)irq2, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(35, (u32)irq3, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(36, (u32)irq4, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(37, (u32)irq5, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(38, (u32)irq6, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(39, (u32)irq7, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(40, (u32)irq8, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(41, (u32)irq9, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(42, (u32)irq10, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(43, (u32)irq11, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(44, (u32)irq12, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(45, (u32)irq13, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(46, (u32)irq14, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);
  idt_create_entry(47, (u32)irq15, IDT_ENTRY_SEL, IDT_ENTRY_FLAGS);

  // load the idt
  idt_load_and_set((u32)&idt_t);

  __asm__ __volatile__ ("sti"); // enable interrupts on the system
}
