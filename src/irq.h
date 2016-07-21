#ifndef IRQ_H
#define IRQ_H

/**
 * http://www.osdever.net/bkerndev/Docs/irqs.htm
 */

#include "common.h"

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

// Handler special type
typedef void (*irq_t)(registers);

// These are ISRs pointing to the IRQ handler
void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();

/** irq_remap:
 * In protected mode, IRQs 0 to 7 conflict with the ISRs already reserved.
 * Consequently a remapping is needed, by sending commands to the programmable
 * interrupt controller (PIC). In this way IRQs 0 to 15 are remapped to IDT
 * entries 32 to 47
 *
 */
void irq_remap();

/** irq_handler:
 * IRQs point to this function when invoking by the kernel.
 * Moreover when an IRQ is finished, it needs to tell the PIC chip
 * the task is done by sending it the end of interrupt (EOI) command (<=> acknowledge a PIC).
 * Finally if the 2nd PIC gets an interrupt (IRQ 8 to 15), we need to acknowledge
 * both PICs, otherwise only the 1st PIC needs to be acknowledged.
 * Warning: if an EOI is not sent, the system is not able to raise IRQs anymore!
 *
 * @param r System registers
 */
void irq_handler(registers r);

/** irq_install_handler:
 * Installs a custom IRQ handler for the given IRQ
 *
 * @param n  The handler number
 * @param handler The handler
 */
void irq_install_handler(u8 n, irq_t handler);

#endif /* IRQ_H */
