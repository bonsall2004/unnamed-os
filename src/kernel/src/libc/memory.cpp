/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#include <cstddef>
#include <memory>
#include <limine.h>
#include <display.h>

__attribute__((used, section(".requests")))
static volatile struct limine_memmap_request memmap_request = { .id = LIMINE_MEMMAP_REQUEST, .revision = 0, .response = nullptr };

void* memcpy(void* dest, const void* src, size_t n)
{
  __asm__ volatile (
    "rep movsb"
    : "=D" (dest), "=S" (src), "=c" (n)
    : "0" (dest), "1" (src), "2" (n)
    : "memory"
    );
  return dest;
}

void* memset(void* s, int c, size_t n)
{
  auto* p = (uint8_t*)s;
  while(n--)
  {
    *p++ = (uint8_t)c;
  }
  return s;
}

int memcmp(const void* s1, const void* s2, size_t n)
{
  const auto* p1 = (const uint8_t*)s1;
  const auto* p2 = (const uint8_t*)s2;

  for(size_t i = 0; i < n; i++)
  {
    if(p1[i] != p2[i])
    {
      return p1[i] - p2[i];
    }
  }
  return 0;
}

typedef struct MemoryBlock
{
  size_t size;
  bool free;
  struct MemoryBlock* next;
} MemoryBlock;

static MemoryBlock* free_list;

void init_allocator()
{
  struct limine_memmap_entry** mmap = memmap_request.response->entries;
  size_t mmap_entries = memmap_request.response->entry_count;

  free_list = nullptr;

  for(size_t i = 0; i < mmap_entries; i++)
  {
    if(mmap[i]->type == LIMINE_MEMMAP_USABLE)
    {
      auto* block = (MemoryBlock*)(size_t*)(mmap[i]->base + 0xFFFF800000000000);
      block->size = mmap[i]->length;
      block->free = true;
      block->next = free_list;
      free_list = block;
    }
  }
}

[[nodiscard]] void* malloc(size_t size)
{
  MemoryBlock* current = free_list;
  while(current != nullptr)
  {
    if(current->free && current->size >= size)
    {
      if(current->size > size + sizeof(MemoryBlock))
      {
        auto* new_block = reinterpret_cast<MemoryBlock*>(reinterpret_cast<void*>(reinterpret_cast<char*>(current) + sizeof(MemoryBlock) + size));
        new_block->size = current->size - size - sizeof(MemoryBlock);
        new_block->free = true;
        new_block->next = current->next;
        current->size = size;
        current->next = new_block;
      }
      current->free = false;
      return reinterpret_cast<void*>(reinterpret_cast<char*>(current) + sizeof(MemoryBlock));
    }
    current = current->next;
  }
  return nullptr;
}

void free(void* ptr)
{
  if(ptr == nullptr) return;

  auto* block = reinterpret_cast<MemoryBlock*>(reinterpret_cast<char*>(ptr) - sizeof(MemoryBlock));
  block->free = true;

  if(block->next && block->next->free)
  {
    block->size += block->next->size + sizeof(MemoryBlock);
    block->next = block->next->next;
  }

  MemoryBlock* current = free_list;
  while(current && current->next != block)
  {
    current = current->next;
  }

  if(current && current->free)
  {
    current->size += block->size + sizeof(MemoryBlock);
    current->next = block->next;
  }
}

void* operator new(size_t size)
{
  return malloc(size);
}

void operator delete(void* ptr) noexcept
{
  free(ptr);
}

void operator delete[](void* ptr) noexcept {
  free(ptr);
}

void operator delete(void* ptr, size_t size) noexcept {
  free(ptr);
}