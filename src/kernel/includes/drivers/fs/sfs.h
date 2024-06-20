//fuck me
// this is the stoner file system 

#pragma once
#include <cstdint>
#include <time.h>

#define MAX_FILES_IN_DIR 256
#define MAX_NAME_LENGTH 255

extern "C" {
typedef struct {
  uintptr_t point_in_dataBlock_to_start;
  int64_t size;
  char name[MAX_NAME_LENGTH];
  unixT_t mode_time;
  bool is_directory;
  struct Directory* sub_directory;
} FileEntry;

typedef struct Directory {
  FileEntry entries[MAX_FILES_IN_DIR];
  int64_t num_entries;
} Directory;

typedef struct {
  int64_t num_block;
  int64_t num_inods;
  uintptr_t data_block_start;
  int64_t data_block_size;
  uintptr_t blocker_point;
  int64_t size_of_index;
} SuperBlock;
}
