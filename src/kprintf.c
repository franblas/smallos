#include "kprintf.h"
#include "io.h"

/* Colors for framebuffer */
#define FB_BLACK 0
#define FB_WHITE 15

/* Rows & Columns sizes */
#define FB_NUM_COLS 80
#define FB_NUM_ROWS 25
#define FB_NUM_TOTAL FB_NUM_COLS*FB_NUM_ROWS

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

#define NULL_CHAR '\0'

/* Global */
char *fb = (char *) 0x000B8000;
u32 cursor_pos = 0;

/* Framebuffer functions */
void move_cursor(u16 pos)
{
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

char read_cell(u32 row, u32 col)
{
  u32 pos = (row * FB_NUM_COLS + col);
  return fb[pos * 2];
}

void write_cell(u32 i, char c, u8 fg, u8 bg)
{
  fb[i * 2] = c;
  fb[i * 2 + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
  move_cursor(cursor_pos);
  cursor_pos++;
}

void new_line(u32 pos)
{
  cursor_pos = ((pos + FB_NUM_COLS) / FB_NUM_COLS) * FB_NUM_COLS;
  move_cursor(cursor_pos);
}

void write_at(u32 pos, char c)
{
  switch(c) {
    case '\n': // new line
      new_line(pos);
      break;
    case '\t': // tab
      move_cursor(cursor_pos + 8);
      break;
    case '\b': // backspace
      cursor_pos = pos - 2;
      move_cursor(cursor_pos);
      write_cell(pos - 1, NULL_CHAR, FB_WHITE, FB_BLACK);
      break;
    default:
      write_cell(pos, c, FB_WHITE, FB_BLACK);
  }
}

void write_char(char c)
{
  if (cursor_pos >= FB_NUM_TOTAL) {
    scroll();
    write_at(cursor_pos, c);
  } else {
    write_at(cursor_pos, c);
  }
}

void screen_write(char str[])
{
  u32 i = 0;
  while(str[i] != NULL_CHAR) {
    write_char(str[i]);
    i++;
  }
}

void scroll()
{
  u32 r, c, pos;
  char buffer[FB_NUM_TOTAL];
  for(r=1; r<FB_NUM_ROWS; r++) {
    for(c=0; c<FB_NUM_COLS; c++) {
      pos = (r * FB_NUM_COLS + c);
      buffer[pos - FB_NUM_COLS] = read_cell(r, c);
    }
  }

  for(c=FB_NUM_TOTAL-FB_NUM_COLS; c<FB_NUM_TOTAL; c++) {
    buffer[c] = NULL_CHAR;
  }

  cursor_pos = 0;
  for(pos=0; pos<FB_NUM_TOTAL; pos++) {
    write_at(pos, buffer[pos]);
  }
  cursor_pos = FB_NUM_TOTAL - FB_NUM_COLS;
}

void clear_screen()
{
  u32 r, c, pos;
  for(r=0; r<FB_NUM_ROWS; r++) {
    for(c=0; c<FB_NUM_COLS; c++) {
      pos = (r * FB_NUM_COLS + c);
      write_at(pos, NULL_CHAR);
    }
  }
  cursor_pos = 0;
}
