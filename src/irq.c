#include "irq.h"
#include "io.h"

#define PIC1_CMD  0x20 // PIC1 = master PIC
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0 // PIC2 = slave PIC
#define PIC2_DATA 0XA1
#define PIC_EOI   0X20  // End of interrupt cmd code

#define IRQ_NB 256

/* Global */
// Array of function pointers to handle custom IRQ handlers for a given IRQ
irq_t irq_routines[IRQ_NB];

/* IRQ functions */
void irq_install_handler(u8 n, irq_t handler)
{
    irq_routines[n] = handler;
}

void irq_remap()
{
    outb(PIC1_CMD, 0x11);
    outb(PIC2_CMD, 0x11);
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    outb(PIC1_DATA, 0x0);
    outb(PIC2_DATA, 0x0);
}

void irq_handler(registers r)
{
    // If the IDT entry that was invoked was greater than 40 (<=> IRQ 8 to 15)
    if (r.int_no >= 40) {
        outb(PIC2_CMD, PIC_EOI); // send reset signal to PIC2
    }

    // In either case
    outb(PIC1_CMD, PIC_EOI); // send reset signal to PIC1

    if (irq_routines[r.int_no] != 0) {
        irq_t handler = irq_routines[r.int_no];
        handler(r);
    }
}
