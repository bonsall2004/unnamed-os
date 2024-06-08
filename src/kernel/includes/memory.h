/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once
#include <stdint.h>
#include <stddef.h>

typedef struct E820_ENTRY_
{
  uint64_t base_address;
  uint64_t length;
  uint32_t type;
  uint32_t attributes;
} e820_entry;

#define MEMORY_MAP ((e820_entry_t*)0x70008)
#define E820_LENGTH (*((uint32_t*)0x70000))

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);