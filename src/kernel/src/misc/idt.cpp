/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#include <cstdint>
#include <idt.h>
#include <cstdio>

struct InterruptDescriptor64
{
  uint16_t offset_1;        // offset bits 0..15
  uint16_t selector;        // a code segment selector in GDT or LDT
  uint8_t ist;              // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
  uint8_t type_attributes;  // gate type, dpl, and p fields
  uint16_t offset_2;        // offset bits 16..31
  uint32_t offset_3;        // offset bits 32..63
  uint32_t zero;            // reserved
};

std::unordered_map<uint16_t, const char*> software_defined_interrupts;

struct idtr
{
  uint16_t limit;
  uint64_t base;
} __attribute__((packed));

struct InterruptDescriptor64 idt[256];
struct idtr idtr;

void set_idt_entry(int num, void (* handler)(interrupt_frame* frame), uint16_t selector, uint8_t flags)
{
  uintptr_t base = (uintptr_t)handler;
  idt[num].offset_1 = base & 0xFFFF;
  idt[num].offset_2 = (base >> 16) & 0xFFFF;
  idt[num].offset_3 = (base >> 32);
  idt[num].selector = selector;
  idt[num].zero = 0;
  idt[num].type_attributes = flags;
}

void load_idt()
{
  idtr.limit = sizeof(idt) - 1;
  idtr.base = (uintptr_t)&idt;
  __asm__ volatile ("lidt %0" : : "m"(idtr));
}

[[noreturn]] __attribute__ ((no_caller_saved_registers))
void handle_exception(const char* message, interrupt_frame* frame, bool clear_screen = true)
{
  __asm__ volatile("cli");
  if(clear_screen)
  {
    fill_frame_buffer(RGB(0x19, 0x19, 0x19, 0xff));
  }
  printf("Interrupt: %s", message);
  printf("Current Instruction Ptr: %p", frame->rip);
  printf("Stack Ptr: %p", frame->rsp);
  while(true)
  {};
}

__attribute__ ((interrupt))
void isr_division_error(interrupt_frame* frame)
{
  handle_exception("Division Error", frame);
}

__attribute__ ((interrupt))
void isr_debug(interrupt_frame* frame)
{
  handle_exception("Debug", frame);
}

__attribute__ ((interrupt))
void isr_non_mask_int(interrupt_frame* frame)
{
  handle_exception("Non Maskable Interrupt", frame);
}

__attribute__ ((interrupt))
void isr_breakpoint(interrupt_frame* frame)
{
  handle_exception("Breakpoint", frame);
}

__attribute__ ((interrupt))
void isr_overflow(interrupt_frame* frame)
{
  handle_exception("Overflow", frame);
}

__attribute__ ((interrupt))
void isr_bound_range_exceeded(interrupt_frame* frame)
{
  handle_exception("Bound Range Exceeded", frame);
}

__attribute__ ((interrupt))
void isr_invalid_opcode(interrupt_frame* frame)
{
  handle_exception("Invalid Opcode", frame);
}

__attribute__ ((interrupt))
void isr_device_not_available(interrupt_frame* frame)
{
  handle_exception("Device Not Available", frame);
}

__attribute__ ((interrupt))
void isr_double_fault(interrupt_frame* frame)
{
  handle_exception("Double Fault", frame);
}

__attribute__ ((interrupt))
void isr_invalid_tss(interrupt_frame* frame)
{
  handle_exception("Invalid TSS", frame);
}

__attribute__ ((interrupt))
void isr_segment_not_present(interrupt_frame* frame)
{
  handle_exception("Segment Not Present", frame);
}

__attribute__ ((interrupt))
void isr_stack_segment_fault(interrupt_frame* frame)
{
  handle_exception("Stack-Segment Fault", frame);
}

__attribute__ ((interrupt))
void isr_general_protection_fault(interrupt_frame* frame)
{
  handle_exception("General Protection Fault", frame);
}

__attribute__ ((interrupt))
void isr_page_fault(interrupt_frame* frame)
{
  handle_exception("Page Fault", frame);
}

__attribute__ ((interrupt))
void isr_alignment_check(interrupt_frame* frame)
{
  handle_exception("Alignment Check", frame);
}

__attribute__ ((interrupt))
void isr_machine_check(interrupt_frame* frame)
{
  handle_exception("Machine Check", frame);
}

__attribute__ ((interrupt))
void isr_control_protection_exception(interrupt_frame* frame)
{
  handle_exception("Control Protection Exception", frame);
}

__attribute__ ((interrupt))
void isr_vmm_communication_exception(interrupt_frame* frame)
{
  handle_exception("VMM Communication Exception", frame);
}

__attribute__ ((interrupt))
void isr_security_exception(interrupt_frame* frame)
{
  handle_exception("Security Exception", frame);
}

__attribute__ ((interrupt))
void isr_virtualization_exception(interrupt_frame* frame)
{
  handle_exception("Virtualization Exception", frame);
}

__attribute__ ((interrupt))
void isr_hypervisor_injection_exception(interrupt_frame* frame)
{
  handle_exception("Hypervisor Injection Exception", frame);
}

__attribute__ ((interrupt))
void isr_software_interrupt(interrupt_frame* frame)
{
  handle_exception("Software Interrupt", frame);
}

__attribute__ ((interrupt))
void isr_x87_float_exception(interrupt_frame* frame)
{
  handle_exception("x87 Floating Point Exception", frame);
}

__attribute__ ((interrupt))
void isr_simd_float_exception(interrupt_frame* frame)
{
  handle_exception("SIMD Floating Point Exception", frame);
}

__attribute__ ((interrupt))
void isr_out_of_range_exception(interrupt_frame* frame)
{
  handle_exception("Out Of Range", frame);
}

__attribute__ ((interrupt))
void isr_software_defined_exception_handler(interrupt_frame* frame)
{
  handle_exception("Out Of Range", frame);
}

void init_idt()
{
  set_idt_entry(0, isr_division_error, 40, 0x8E);
  set_idt_entry(1, isr_debug, 40, 0x8E);
  set_idt_entry(2, isr_non_mask_int, 40, 0x8E);
  set_idt_entry(3, isr_breakpoint, 40, 0x8E);
  set_idt_entry(4, isr_overflow, 40, 0x8E);
  set_idt_entry(5, isr_bound_range_exceeded, 40, 0x8E);
  set_idt_entry(6, isr_invalid_opcode, 40, 0x8E);
  set_idt_entry(7, isr_device_not_available, 40, 0x8E);
  set_idt_entry(8, isr_double_fault, 40, 0x8E);
  set_idt_entry(10, isr_invalid_tss, 40, 0x8E);
  set_idt_entry(11, isr_segment_not_present, 40, 0x8E);
  set_idt_entry(12, isr_stack_segment_fault, 40, 0x8E);
  set_idt_entry(13, isr_general_protection_fault, 40, 0x8E);
  set_idt_entry(14, isr_page_fault, 40, 0x8E);
  set_idt_entry(16, isr_x87_float_exception, 40, 0x8E);
  set_idt_entry(17, isr_alignment_check, 40, 0x8E);
  set_idt_entry(18, isr_machine_check, 40, 0x8E);
  set_idt_entry(19, isr_simd_float_exception, 40, 0x8E);
  set_idt_entry(20, isr_virtualization_exception, 40, 0x8E);
  set_idt_entry(21, isr_control_protection_exception, 40, 0x8E);
  set_idt_entry(28, isr_hypervisor_injection_exception, 40, 0x8E);
  set_idt_entry(29, isr_vmm_communication_exception, 40, 0x8E);
  set_idt_entry(30, isr_security_exception, 40, 0x8E);
  set_idt_entry(40, isr_out_of_range_exception, 40, 0x8E);

  // Task scheduler Interrupt
  set_idt_entry(45, scheduler_interrupt, 40, 0x8E);

  set_idt_entry(127, isr_software_defined_exception_handler, 40, 0x8E);
  set_idt_entry(128, isr_software_interrupt, 40, 0x8E);

  load_idt();
  __asm__ volatile("sti");
}