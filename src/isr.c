#include "isr.h"
#include "framebuffer.h"

#define EXCEPTIONS_NB 32
#define DEFINED_EXCEPTIONS_NB 19

/* Global */
// Exception messages
char *exception_msg[DEFINED_EXCEPTIONS_NB] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault Exception",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check Exception"
};

/* ISR functions */
void isr_handler(registers r)
{
    u32 n_interupt = r.int_no;
    if (n_interupt<EXCEPTIONS_NB && n_interupt>DEFINED_EXCEPTIONS_NB-1) {
        screen_write("Received a reserved interrupt!");
    }
    else if (n_interupt<=DEFINED_EXCEPTIONS_NB-1) {
        screen_write(exception_msg[n_interupt]);
    } else {
        screen_write("Unknown interrupt");
    }
    for (;;); // handle forever
}
