#include <cstdio>
#include <display.h>
#include <memory>
#include <k_entry.h>
#include <idt.h>
#include <pair>
#include <function>
#include <vector>
#include <scheduling/TaskScheduler.h>
#include <srand>
#include <unique_ptr>
#include <atomic>
#include "shared_ptr"

extern void (*__init_array[])();
extern void (*__init_array_end[])();

void kernel_main();

extern "C" {
__attribute__((used))
void _start()
{
  kernel_main();
}
}

int testf(int a, int b)
{
  return a + b;
}

void kernel_main()
{
  init_idt();
  init_allocator();

  for (size_t i = 0; &__init_array[i] != __init_array_end; i++) {
    __init_array[i]();
  }

  init_task_scheduler();
  std::srand(100);
  auto* test = (color_t*)malloc(sizeof(color_t));
  std::function<int(int, int)> testFunc = testf;
  testFunc = [](int a, int b)
  { return a - b; };
  *test = RGB(0, 0, testFunc(100, 155), std::rand(1, 255));
  std::atomic<bool> testAtomic(true);

  int (* test1)(int, int) = [](int a, int b)
  { return a + b; };

  fill_frame_buffer(*test);
  if(testAtomic.load())
  {
    printf("PP");

  }

  testAtomic.store(true);
  if(testAtomic.load())
  {
    printf("PP");
  }

  free(test);
  printf("Pointer: %p", test);

  KERNEL_LOOP_END
}
