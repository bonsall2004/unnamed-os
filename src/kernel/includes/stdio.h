/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once
#include "stdint.h"

void putc_colour(char character, uint8_t color);
void putc(char character);
void puts(const char* message);
void printf(const char* fmt, ...);

void clear_screen();