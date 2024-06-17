/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#define INITIAL_STACK_SIZE 1024

typedef struct context
{
  uint64_t r15;
  uint64_t r14;
  uint64_t r13;
  uint64_t r12;
  uint64_t r11;
  uint64_t r10;
  uint64_t r9;
  uint64_t r8;
  uint64_t rbp;
  uint64_t rdi;
  uint64_t rsi;
  uint64_t rdx;
  uint64_t rcx;
  uint64_t rbx;
  uint64_t rax;
  uint64_t rip;
  uint64_t cs;
  uint64_t rflags;
  uint64_t rsp;
  uint64_t ss;
} context_t;

struct ThreadControlBlock
{
  context_t thread_context;
  uint64_t thread_id;
  enum State
  {
    RUNNING, READY, DEAD, SLEEPING
  } state;
};

extern "C" void scheduler_handler(context_t* ctx);

bool init_task_scheduler();

class TaskQueue
{
  private:
    std::vector<ThreadControlBlock*> tasks;
    size_t current_task_index = 0;
    size_t thread_id_inc = 0;

  public:
    TaskQueue();
    ~TaskQueue();

    ThreadControlBlock* create_task(void(* task_func)());
    void add_task(ThreadControlBlock* tcb);
    ThreadControlBlock* get_current_task();
    ThreadControlBlock* get_next_task();

};

extern TaskQueue* main_task_queue;