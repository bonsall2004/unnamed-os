/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once
#include <unordered_map>
#include <function>

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

extern std::unordered_map<uint16_t, const char*> software_defined_interrupts;

#define UNIQUE_NAME(base) CONCAT(base, __LINE__)
#define CONCAT(base, line) base##line

#define REGISTER_KERNEL_PANIK(num, msg)
namespace {
    struct UNIQUE_NAME(KernelPanikHandler)
    {
        UNIQUE_NAME(KernelPanikHandler)(uint16_t n, const char* m)
        {
            software_defined_interrupts.insert(n, m);
        }
    };
    static UNIQUE_NAME(KernelPanikHandler) UNIQUE_NAME(handler_instance)(num, msg);
}