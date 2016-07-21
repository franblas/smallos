#include "framebuffer.h"
#include "gdt.h"
#include "idt.h"
#include "keyboard.h"

int kmain()
{
  gdt_init();
  idt_init();
  keyboard_init();

  clear_screen();
  screen_write("-------------------------\n");
  screen_write("Welcome to small OS!\n");
  screen_write("-------------------------\n\n");

  return 0;
}
