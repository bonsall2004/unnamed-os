/*
 * custom_os
 * Author: bonsall2004
 * Description:
 */
#include "stdbool.h"
#include <stdio.h>

typedef struct TEXT_CELL_
{
  uint8_t character;
  uint8_t color;
} text_cell_t;

static uint16_t character_offset = 0;
static uint8_t line = 0;

void putc_colour(char character, uint8_t color)
{
  *((text_cell_t*)0xB8000 + character_offset++) = (text_cell_t){ .character=character, .color=color };
}

void putc(char character)
{
  putc_colour(character, 0x0f);
}

void puts(const char* message)
{
  character_offset = line * 80;
  for(int i = 0; message[i] != '\0'; i++)
  {
    putc_colour(message[i], 0x0D);
  }
  line++;
}

void clear_screen()
{
  for(uint16_t i = 0; i < 1920; i++)
  {
    putc(' ');
  }
}
