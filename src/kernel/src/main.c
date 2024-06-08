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

  KERNEL_LOOP_END
}