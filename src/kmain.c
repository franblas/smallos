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
  // kprint("-------------------------\n");
  // kprint("Welcome to small OS!\n");
  // kprint("-------------------------\n\n");

  vga_init();
  blue_screen();

  return 0;
}
