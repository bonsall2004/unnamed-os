#include <cstdio>
#include <display.h>
#include <memory>
#include "cstddef"
#include "k_entry.h"


__attribute__((used))
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