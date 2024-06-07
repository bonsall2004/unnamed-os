#include "./definitions.h"

void *memcpy(void *dest, const void *src, size_t n) {
    // Inline assembly for x86_64 using the `rep movsb` instruction
    __asm__ volatile (
        "rep movsb"
        : "=D" (dest), "=S" (src), "=c" (n)
        : "0" (dest), "1" (src), "2" (n)
        : "memory"
    );
    return dest;
}
