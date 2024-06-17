/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#include <scheduling/TaskScheduler.h>

TaskQueue::TaskQueue() : current_task_index(0)
{
};

TaskQueue* main_task_queue;

[[noreturn]] void idle_thread_task()
{
  while(true)
    __asm__ volatile("hlt");
}

bool init_task_scheduler()
{
  main_task_queue = static_cast<TaskQueue*>(malloc(sizeof(TaskQueue)));
  if(!main_task_queue) return false;

  main_task_queue->add_task(main_task_queue->create_task(idle_thread_task));
  return true;
}

void TaskQueue::add_task(ThreadControlBlock* tcb)
{
  tasks.push_back(tcb);
}

ThreadControlBlock* TaskQueue::get_current_task()
{
  return tasks[current_task_index];
}
ThreadControlBlock* TaskQueue::create_task(void(* task_func)())
{
  auto* tcb = new ThreadControlBlock();
  if(!tcb) return nullptr;

  tcb->state = ThreadControlBlock::READY;
  tcb->thread_id = this->thread_id_inc++;
  tcb->thread_context.rflags = 0x202;
  tcb->thread_context.rip = reinterpret_cast<uintptr_t>(task_func);
  tcb->thread_context.rsp = 0x1000000;

  return tcb;
}

ThreadControlBlock* TaskQueue::get_next_task()
{
  if(tasks.size() == 0) return nullptr;
  current_task_index = (current_task_index + 1) % tasks.size();
  return tasks[current_task_index];
}

extern "C" void scheduler_handler(context_t* ctx)
{
  main_task_queue->get_current_task()->thread_context = *ctx;
  main_task_queue->get_current_task()->state = ThreadControlBlock::READY;
  do
  {}
  while(main_task_queue->get_next_task()->state != ThreadControlBlock::READY);

  *ctx = main_task_queue->get_current_task()->thread_context;
  main_task_queue->get_current_task()->state = ThreadControlBlock::RUNNING;
}
