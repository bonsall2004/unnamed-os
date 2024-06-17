/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#include <cstddef>
#include <cstring>

const char* strchr(const char* str, char chr)
{
  if(str == nullptr)
  {
    return nullptr;
  }

  while(*str)
  {
    if(*str == chr)
    {
      return str;
    }

    ++str;
  }

  return nullptr;
}

char* strcpy(char* dst, const char* src)
{
  char* orig_dest = dst;

  if(dst == nullptr)
  {
    return nullptr;
  }

  if(src == nullptr)
  {
    *dst = '\0';
    return dst;
  }

  while(*src)
  {
    *dst = *src;
    src++;
    dst++;
  }

  *dst = '\0';
  return orig_dest;
}

size_t strlen(const char* str)
{
  size_t len = 0;
  while(*str)
  {
    len++;
    str++;
  }

  return len;
}