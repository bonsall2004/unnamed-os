/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once
#include "stdint.h"

#define VGA_WIDTH 480
#define VGA_HEIGHT 360
#define VGA_ADDRESS 0xA0000

void set_pixel(int x, int y, uint8_t color);