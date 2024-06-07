#include <stdio.h>
#include "stdbool.h"

typedef struct TEXT_CELL_
{
  uint8_t character;
  uint8_t color;
} text_cell_t;

void putc(char character, uint8_t color, uint16_t offset)
{
  *((text_cell_t*)0xB8000 + offset) = (text_cell_t){ .character=character, .color=color };
}

void puts(const char* message)
{
  for(int i = 0; message[i] != '\0'; i++)
  {
    putc(message[i], 0x0D, i);
  }
}

void clear_screen()
{
  for(uint16_t i = 0; i < 1920; i++)
  {
    putc(' ', 0x00, i);
  }
}