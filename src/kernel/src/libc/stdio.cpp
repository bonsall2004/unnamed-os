/*
 * custom_os
 * Author: bonsall2004
 * Description:
 */
#include <display.h>
#include <cstdio>
#include <cstdarg>

uint16_t cursor_pos_x = 6;
uint16_t cursor_pos_y = 6;

void putc_colour(char character, color_t color)
{
  if(character == '\n' || character == '\r')
  {
    cursor_pos_x = 6;
    cursor_pos_y = cursor_pos_y + 12 > FRAME_BUFFER_HEIGHT ? 12 : cursor_pos_y + 12;
    return;
  }

  if(cursor_pos_x + 8 > FRAME_BUFFER_WIDTH)
  {
    cursor_pos_x = 0;
    cursor_pos_y += 12;
  }
  const uint8_t* cf = &fontdata[character * 8];
  for(int y = 0; y < 8; y++)
  {
    for(int x = 0; x < 8; x++)
    {
      if((cf[y] & (1 << (7 - x))) != 0)
      {
        draw_pixel(cursor_pos_x + x, cursor_pos_y + y, color);
      }
    }
  }
  cursor_pos_x += 12;
}

void putc(char character)
{
  putc_colour(character, RGB(0xFF, 0xFF, 0xFF, 0xff));
}

void puts(const char* str)
{
  while(*str)
  {
    putc(*str++);
  }
}

void puts(const char* str, color_t color)
{
  while(*str)
  {
    putc_colour(*str++, color);
  }
}

void itoa(int value, char* str, int base)
{
  char* ptr = str, * ptr1 = str, tmp_char;
  int tmp_value;

  if(value < 0 && base == 10)
  {
    value = -value;
    *ptr++ = '-';
  }

  tmp_value = value;

  do
  {
    int remainder = tmp_value % base;
    *ptr++ = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'a');
  }
  while(tmp_value /= base);

  *ptr-- = '\0';

  while(ptr1 < ptr)
  {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
}

void utoa(uintptr_t value, char* str, int base)
{
  char* ptr = str, * ptr1 = str, tmp_char;
  uintptr_t tmp_value;

  tmp_value = value;

  do
  {
    uintptr_t remainder = tmp_value % base;
    *ptr++ = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'a');
  }
  while(tmp_value /= base);

  *ptr-- = '\0';

  while(ptr1 < ptr)
  {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
}

void printf(const char* format, ...)
{
  va_list args;
  va_start(args, format);

  color_t color = RGB(0xff, 0xff, 0xff, 0xff);

  if(cursor_pos_y > FRAME_BUFFER_HEIGHT)
  {
    cursor_pos_y = 6;
  }

  const char* p = format;
  while(*p)
  {
    if(*p == '%')
    {
      p++;
      int width = 0;
      while(*p >= '0' && *p <= '9')
      {
        width = width * 10 + (*p - '0');
        p++;
      }
      switch(*p)
      {
      case 'c':
      {
        char c = (char)va_arg(args, int);
        putc(c);
        break;
      }
      case 's':
      {
        char* str = va_arg(args, char *);
        puts(str, color);
        break;
      }
      case 'd':
      case 'i':
      {
        int num = va_arg(args, int);
        char str[12];  // Enough to hold a 32-bit int
        itoa(num, str, 10);
        puts(str, color);
        break;
      }
      case 'u':
      {
        unsigned int num = va_arg(args, unsigned int);
        char str[12];  // Enough to hold a 32-bit unsigned int
        utoa(num, str, 10);
        puts(str, color);
        break;
      }
      case 'x':
      {
        unsigned int num = va_arg(args, unsigned int);
        char str[9];  // Enough to hold a 32-bit hex number
        utoa(num, str, 16);
        puts(str, color);
        break;
      }
      case 'X':
      {
        unsigned int num = va_arg(args, unsigned int);
        char str[9];  // Enough to hold a 32-bit hex number
        utoa(num, str, 16);
        for(char* s = str; *s; s++)
        {
          if(*s >= 'a' && *s <= 'f')
          {
            *s -= 32;  // Convert to uppercase
          }
        }
        puts(str, color);
        break;
      }
      case 'o':
      {
        unsigned int num = va_arg(args, unsigned int);
        char str[12];  // Enough to hold a 32-bit octal number
        utoa(num, str, 8);
        puts(str, color);
        break;
      }
      case 'p':
      {
        uintptr_t num = (uintptr_t)va_arg(args, void *);
        char str[19];  // Enough to hold a pointer address
        puts("0x", color);
        utoa(num, str, 16);
        puts(str, color);
        break;
      }
      case '%':
      {
        putc_colour('%', color);
        break;
      }
      default:
      {
        putc_colour('%', color);
        putc_colour(*p, color);
        break;
      }
      }
    }
    else
    {
      putc_colour(*p, color);
    }
    p++;
  }
  va_end(args);
  cursor_pos_x = 6;
  cursor_pos_y += 12;
}