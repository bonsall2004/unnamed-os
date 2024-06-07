#include "stdbool.h"
#include <stdio.h>

__attribute__((used))
void initialize_kernel()
{
  clear_screen();
  putc(':', 0x0D, 1205);
  putc('3', 0x0D, 1206);
  puts("slayingg rn");
  asm("hlt");
  while(true)
  {

  }
}