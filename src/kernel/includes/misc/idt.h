/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once

struct interrupt_frame
{
  uint64_t rip;
  uint64_t cs;
  uint64_t rflags;
  uint64_t rsp;
  uint64_t ss;
};


extern "C" void scheduler_interrupt(interrupt_frame* frame);
void init_idt();

