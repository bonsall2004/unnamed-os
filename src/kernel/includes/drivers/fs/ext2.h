//olivia
//10:37

#pragma once
#include <cstdint>
#include <time.h>


// ill dead if i have tk move from uint to int 
typedef struct{
  uint32_t s_inodes_count;
  uint32_t s_blocks_count;
  uint32_t s_r_blocks_count;
  uint32_t s_free_blocks_count;
  uint32_t s_free_inodes_count;
  uint32_t s_first_data_block;
  uint32_t s_log_block_size;
  uint32_t s_blocks_per_group;
  uint32_t s_frags_per_group;
  uint32_t s_inodes_per_group;
  unixT_t s_mtime;
  unixT_t s_wtime;
  uint16_t s_mnt_count;
  uint16_t s_max_mnt_count;
  uint16_t s_magic;
  uint16_t s_state;
  uint16_t s_errors;
  uint16_t s_minor_rev_level;
  unixT_t s_lastcheck;
  unixT_t s_checkinterval;
  uint32_t s_creator_os;
  uint32_t s_rev_level;
  uint16_t s_def_resuid;
  uint32_t s_first_ino;
  uint16_t s_inode_size;
  uint16_t s_block_group_nr;
  uint32_t s_feature_compat;
  uint32_t s_feature_incompat;
  uint32_t s_feature_ro_compat;
  char s_uuid[16];
  uint16_t s_volume_name;
  uint64_t s_last_mounted;
  uint32_t s_algo_bitmap;
  uint8_t s_prealloc_blocks;
  uint8_t s_prealloc_dir_blocks;
  uint16_t s_journal_uuid;
  uint32_t s_journal_inum;
  uint32_t s_journal_dev;
  uint32_t s_last_orphan;
  uint32_t s_hash_seed[4];
  uint8_t s_def_hash_version;
  uint32_t s_default_mount_options;
  uint32_t s_first_meta_bg;
}block;
