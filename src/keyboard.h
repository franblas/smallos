#ifndef KEYBOARD_H#define KEYBOARD_H/** * http://wiki.osdev.org/PS/2_Keyboard */#include "common.h"/** keyboard_handler: * Handle the kayboard (callback). * * @param r System registers */void keyboard_handler(registers r);/** keyboard_init: * Initialize the PS/2 keyboard chip. * */void keyboard_init();#endif /* KEYBOARD_H */