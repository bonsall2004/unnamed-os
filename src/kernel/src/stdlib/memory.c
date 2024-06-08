/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#include <stddef.h>
#include <memory.h>

void *memcpy(void *dest, const void *src, size_t n) {
  __asm__ volatile (
    "rep movsb"
    : "=D" (dest), "=S" (src), "=c" (n)
    : "0" (dest), "1" (src), "2" (n)
    : "memory"
    );
  return dest;
}

void *memset(void *s, int c, size_t n) {
  uint8_t *p = (uint8_t*)s;
  while (n--) {
    *p++ = (uint8_t)c;
  }
  return s;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const uint8_t *p1 = (const uint8_t *)s1;
  const uint8_t *p2 = (const uint8_t *)s2;

  for (size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return p1[i] - p2[i];
    }
  }
  return 0;
}
