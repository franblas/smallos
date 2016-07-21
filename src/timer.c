#include "io.h"
#include "irq.h"
#include "framebuffer.h"

#define TIMER_CMD 0x43
#define TIMER_CHANNEL_0_DATA 0x40

/* Global */
u32 timer_ticks = 0; // Number of ticks the system has been running for

/* Timer functions */
void timer_handler(registers r)
{
    (void)r;

    timer_ticks++;

    // Every 18 clocks (~= 1sec), it displays a message on the screen
    if (timer_ticks % 18 == 0) {
        screen_write("A tick ");
    }
}

void timer_init(u32 frequency)
{
    // Installs 'timer_handler' to IRQ0
    irq_install_handler(IRQ0, &timer_handler);

    u32 divisor = 1193180 / frequency; // Calculate the divisor

    // send the PIT command
    outb(TIMER_CMD, 0x36);

    // send frequency divisor
    outb(TIMER_CHANNEL_0_DATA, divisor & 0xFF);
    outb(TIMER_CHANNEL_0_DATA, divisor >> 8);
}
