#ifndef VGA_H#define VGA_H#include "common.h"/** write_registers: * Write into graphical card registers regarding a set of instructions * * @param graphical_mode The array of instructions for graphical mode setup */void write_registers(u8* graphical_mode);/** set_mode: * Setup a specific VGA graphical mode * * @param width Width of the screen * @param height Height of the screen * @param color_depth Color depth mode for the screen */void set_mode(u32 width, u32 height, u32 color_depth);/** supported_mode: * Check the existance of a VGA mode * * @param width Width of the screen * @param height Height of the screen * @param color_depth Color depth mode for the screen */bool supported_mode(u32 width, u32 height, u32 color_depth);/** put_pixel: * Set a pixel on coordinates with a defined color * * @param x The absciss coordinate * @param y The ordinate coordinate * @param color_code Ther color code of the pixel */void put_pixel(u32 x, u32 y, u8 color_code);/** put_pixel: * Get the framebuffer segment address regarding the mode used * */// u8* get_fb_segment();/** vga_init: * Initialize the VGA mode * */void vga_init();/** blue_screen: * Color the full screen in blue * */void blue_screen();#endif /* VGA_H */