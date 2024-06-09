#include <cstdio>
#include <display.h>
#include <memory>
#include "cstddef"
#include "k_entry.h"
#include "idt.h"

__attribute__((used))
void _start()
{
  init_idt();
  init_allocator();

  auto* test = (color_t*)malloc(sizeof(color_t));
  *test = RGB(10, 0, 255, 255);

  fill_frame_buffer(*test);
  free(test);
  printf("Pointer: %p", test);

  KERNEL_LOOP_END
}