#include "gdt.h"

#define GDT_NUM_ENTRIES 5

/* Global */
gdt_table gdt_t; // gdt table
gdt_entry gdt_entries[GDT_NUM_ENTRIES]; // gdt entries

/* GDT functions */
void gdt_create_entry(u32 n, u16 base_low, u8 base_mid, u8 base_high, u16 limit, u8 access, u8 others)
{
  gdt_entries[n].limit = limit;
  gdt_entries[n].base_low = base_low;
  gdt_entries[n].base_mid = base_mid;
  gdt_entries[n].access = access;
  gdt_entries[n].others = others & 0xF0;
  gdt_entries[n].base_high = base_high;
}

void gdt_init()
{
  // initialize gdt table
  gdt_t.size = (sizeof (gdt_entry) * GDT_NUM_ENTRIES) - 1;
  gdt_t.address = (u32)&gdt_entries;

  // initialize gdt entries
  gdt_create_entry(0, 0, 0, 0, 0, 0, 0); // null entry
  gdt_create_entry(1, 0, 0, 0, 0xFFFF, 0x9A, 0xCF); // kernel code
  gdt_create_entry(2, 0, 0, 0, 0xFFFF, 0x92, 0xCF); // kernel data
  gdt_create_entry(3, 0, 0, 0, 0xFFFF, 0xFA, 0xCF); // user code
  gdt_create_entry(4, 0, 0, 0, 0xFFFF, 0xF2, 0xCF); // user data

  // load the gdt
  gdt_load_and_set((u32)&gdt_t);
}
