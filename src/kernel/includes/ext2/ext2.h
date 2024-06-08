/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once
#include "../stdint.h"

typedef struct
{
  uint32_t bitmap_block_addr;
  uint32_t bitmap_inode_addr;
  uint32_t inode_table_start_addr;
  uint16_t unallocated_block_count;
  uint16_t unallocated_inode_count;
  uint16_t directory_count;
} ext_block_group_descriptor;