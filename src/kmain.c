#include "kprintf.h"
#include "gdt.h"
#include "idt.h"
#include "keyboard.h"
#include "vga.h"

int kmain()
{
  gdt_init();
  idt_init();
  keyboard_init();

  // clear_screen();
  // screen_write("-------------------------\n");
  // screen_write("Welcome to small OS!\n");
  // screen_write("-------------------------\n\n");

  vga_init();

  u32 x;
  u32 y;
  for (x=0; x<320; x++) {
    for(y=0; y<200; y++) {
      put_pixel(x, y, 0x09);
    }
  }

  return 0;
}
