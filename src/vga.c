#include "vga.h"
#include "io.h"

#define MISC_PORT 0x3C2
#define CRTC_INDEX_PORT 0x3D4
#define CRTC_DATA_PORT 0x3D5
#define SEQUENCER_INDEX_PORT 0x3C4
#define SEQUENCER_DATA_PORT 0x3C5
#define GRAPHICS_CONTROLLER_INDEX_PORT 0x3CE
#define GRAPHICS_CONTROLLER_DATA_PORT 0x3CF
#define ATTRIBUTE_CONTROLLER_INDEX_PORT 0x3C0
#define ATTRIBUTE_CONTROLLER_READ_PORT 0x3C1
#define ATTRIBUTE_CONTROLLER_WRITE_PORT 0x3C0
#define ATTRIBUTE_CONTROLLER_RESET_PORT 0x3DA

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

#define VGA_MODE_WIDTH 320
#define VGA_MODE_HEIGHT 200
#define VGA_MODE_COLOR_DEPTH 256

u8 *vga_fb = (u8*)0xA0000;

u8 graphical_mode_320x200x256[] = {
/* MISC */
	0x63,
/* SEQ */
	0x03, 0x01, 0x0F, 0x00, 0x0E,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
	0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x9C, 0x0E, 0x8F, 0x28,	0x40, 0x96, 0xB9, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	0x41, 0x00, 0x0F, 0x00,	0x00
};

u8 text_mode_80x25_text[] = {
/* MISC */
	0x67,
/* SEQ */
	0x03, 0x00, 0x03, 0x00, 0x02,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81, 0xBF, 0x1F,
	0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x50,
	0x9C, 0x0E, 0x8F, 0x28, 0x1F, 0x96, 0xB9, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00
};

void write_registers(u8* graphical_mode)
{
  u8 j;

  outb(MISC_PORT, *graphical_mode);
  graphical_mode++;

  for (j=0; j<5; j++) {
    outb(SEQUENCER_INDEX_PORT, j);
    outb(SEQUENCER_DATA_PORT, *graphical_mode);
    graphical_mode++;
  }

  outb(CRTC_INDEX_PORT, 0x03);
  outb(CRTC_DATA_PORT, inb(CRTC_DATA_PORT) | 0x80);
  outb(CRTC_INDEX_PORT, 0x11);
  outb(CRTC_DATA_PORT, inb(CRTC_DATA_PORT) & ~0x80);

  graphical_mode[0x03] |= 0x80;
  graphical_mode[0x11] &= ~0x80;

  for (j=0; j<25; j++) {
    outb(CRTC_INDEX_PORT, j);
    outb(CRTC_DATA_PORT, *graphical_mode);
    graphical_mode++;
  }

  for (j=0; j<9; j++) {
    outb(GRAPHICS_CONTROLLER_INDEX_PORT, j);
    outb(GRAPHICS_CONTROLLER_DATA_PORT, *graphical_mode);
    graphical_mode++;
  }

  for (j=0; j<21; j++) {
    (void)inb(ATTRIBUTE_CONTROLLER_RESET_PORT);
    outb(ATTRIBUTE_CONTROLLER_INDEX_PORT, j);
    outb(ATTRIBUTE_CONTROLLER_WRITE_PORT, *graphical_mode);
    graphical_mode++;
  }

  (void)inb(ATTRIBUTE_CONTROLLER_RESET_PORT);
  outb(ATTRIBUTE_CONTROLLER_INDEX_PORT, 0x20);
}

void set_mode(u32 width, u32 height, u32 color_depth)
{
  if (!supported_mode(width, height, color_depth)) {
    return;
  }
  write_registers(graphical_mode_320x200x256);
}

bool supported_mode(u32 width, u32 height, u32 color_depth)
{
  return width == VGA_MODE_WIDTH && height == VGA_MODE_HEIGHT && color_depth == VGA_MODE_COLOR_DEPTH;
}

// u8* get_fb_segment()
// {
//   outb(GRAPHICS_CONTROLLER_INDEX_PORT, 0x06);
//   u8 segment_nb = inb(GRAPHICS_CONTROLLER_DATA_PORT) & (3<<2);
//
//   switch(segment_nb) {
//     case 0<<2: return (u8*)0x00000;
//     case 1<<2: return (u8*)0xA0000;
//     case 2<<2: return (u8*)0xB0000;
//     case 3<<2: return (u8*)0xB8000;
//   }
//   return (u8*)0x00000;
// }

void put_pixel(u32 x, u32 y, u8 color_code)
{
  if (x > VGA_MODE_WIDTH || y > VGA_MODE_HEIGHT) {
    return;
  }

  u8* pixel_address = vga_fb + VGA_MODE_WIDTH*y + x;
  *pixel_address = color_code;
}

void vga_init()
{
  set_mode(VGA_MODE_WIDTH, VGA_MODE_HEIGHT, VGA_MODE_COLOR_DEPTH);
}
