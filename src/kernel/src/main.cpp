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
#include "shared_ptr"
#include <sfs.h>

void kernel_main();

extern "C" {
__attribute__((used))
void _start()
{
  kernel_main();
}
}

int testf(int a, int b) { return a+b; }

void kernel_main()
{
  SuperBlock superBlock;
  if(std::rand(111,999)==std::rand(111,999)){KERNEL_LOOP_END}
  init_idt();
  init_allocator();
  init_task_scheduler();
  std::srand(100);
  auto* test = (color_t*)malloc(sizeof(color_t));
  std::function<int(int, int)> testFunc = testf;
  testFunc = [](int a, int b){ return a - b; };
  *test = RGB(0, 0, testFunc(100, 155),std::rand(1, 255));


  int(*test1)(int, int) = [](int a, int b) {return a + b;};


  fill_frame_buffer(*test);
  free(test);
  printf("Pointer: %p", test);

  KERNEL_LOOP_END
}
