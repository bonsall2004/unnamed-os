#include <cstdio>
#include <display.h>
#include <memory>
#include <k_entry.h>
#include <idt.h>
#include <pair>
#include <vector>
#include <scheduling/TaskScheduler.h>
#include <srand>

void kernel_main();

extern "C" {
__attribute__((used))
void _start()
{
  kernel_main();
}
}

void kernel_main()
{
  init_idt();
  init_allocator();
  init_task_scheduler();
  std::srand(100);
  auto* test = (color_t*)malloc(sizeof(color_t));
  *test = RGB(std::rand(1, 255), std::rand(1, 255), std::rand(1, 255),std::rand(1, 255));

  fill_frame_buffer(*test);
  free(test);
  printf("Pointer: %p", test);

  KERNEL_LOOP_END
}
