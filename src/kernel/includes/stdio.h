/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once
#include "stdint.h"

void putc(char character, uint8_t color, uint16_t offset);
void puts(const char* message);
void clear_screen();