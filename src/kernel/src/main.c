#include <stdbool.h>
#include <stdio.h>
#include <display.h>
#include <memory.h>
#include "stddef.h"
#include "k_entry.h"


_Noreturn __attribute__((used))
void _start()
{
  init_allocator();
  color_t* test = (color_t*)malloc(sizeof(color_t));
  *test = RGB(0, 0, 255, 255);
  fill_frame_buffer(*test);
  free(test);
  printf("Pointer: %p", test);

  KERNEL_LOOP_END
}