/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#include <stdint.h>
#include <stddef.h>
#include <display.h>

void set_pixel(int x, int y, uint8_t color) {
  uint16_t offset = y * VGA_WIDTH + x;
  *(size_t*)(VGA_ADDRESS + offset) = color;
}