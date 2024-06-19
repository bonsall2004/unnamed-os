//olivia
//16:39
#pragma once
#include <cstdint>

#define MAX_FILENAME_LENGTH 255
#define MAX_FILES 1024
#define MAX_BLOCKS 8192
#define BLOCK_SIZE 4096

typedef struct {
  uint32_t total_inodes;
  uint32_t total_blocks;
  uint32_t free_inodes;
  uint32_t free_blocks;
  uint32_t block_size;
} Superblock;

typedef struct {
  uint32_t inode_number;
  uint32_t file_size;
  uint32_t blocks[MAX_BLOCKS];
  uint16_t permissions;
  uint16_t uid;
  uint16_t gid;
  uint32_t creation_time;
  uint32_t modification_time;
  uint32_t access_time;
} Inode;

typedef struct {
  char filename[MAX_FILENAME_LENGTH];
  uint32_t inode_number;
} DirectoryEntry;

typedef struct {
  DirectoryEntry entries[MAX_FILES];
  uint32_t entry_count;
} Directory;

typedef struct {
  Superblock superblock;
  Inode inodes[MAX_FILES];
  Directory root_directory;
  uint8_t data_blocks[MAX_BLOCKS][BLOCK_SIZE];
} FileSystem;
