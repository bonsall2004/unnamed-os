/*
 * custom_os
 * Author: bonsall2004
 * Description:
 */
#pragma once
#include "stdint.h"
#include "limine.h"

#define FRAME_BUFFER_HEIGHT framebuffer_request.response->framebuffers[0]->height
#define FRAME_BUFFER_WIDTH framebuffer_request.response->framebuffers[0]->width
#define FRAME_BUFFER_PITCH framebuffer_request.response->framebuffers[0]->pitch
#define DEFAULT_FRAME_BUFFER framebuffer_request.response->framebuffers[0]

extern volatile struct limine_framebuffer_request framebuffer_request;

typedef struct color {
  uint8_t rgb[4];
} color_t;

color_t RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void draw_pixel(uint16_t x, uint16_t y, color_t color);
void fill_frame_buffer(color_t color);