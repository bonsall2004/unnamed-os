#include <stdbool.h>
#include <stdio.h>
#include <display.h>
#include "stddef.h"
#include "k_entry.h"

_Noreturn __attribute__((used))
void _start()
{
  fill_frame_buffer(RGB(0xff, 0x00,0xff,0xff));



  KERNEL_LOOP_END
}