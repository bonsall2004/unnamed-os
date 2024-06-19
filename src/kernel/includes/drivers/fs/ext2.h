//olivia
//10:37

#pragma once
#include <cstdint>
#include <time.h>


extern "C"
{
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
}SupurBlock;

//fuck standers
typedef struct{
  uint32_t bg_block_bitmap;
  uint32_t bg_inode_bitmap;
  uint16_t bg_free_blocks_count;
  uint16_t bg_free_inodes_count;
  uint16_t bg_used_dirs_count;
  uint16_t bg_pad;
  char bg_reserved[12];
}BGBT;

typedef struct{
  uint16_t i_mode;
  uint16_t i_uid;
  int32_t i_size;
  uint32_t i_atime;
  uint32_t i_ctime;
  uint32_t i_mtime;
  uint32_t i_dtime;
  uint16_t i_gid;
  uint16_t i_links_count;
  uint32_t i_blocks;
  uint32_t i_flags;
  uint32_t i_osd1;
  uint32_t Hurd;
  uint32_t Linux;
  uint32_t Masix;
  uint32_t i_block[15];
  uint32_t i_generation;
  uint32_t i_file_acl;
  uint32_t i_dir_acl;
  uint32_t i_faddr;
}Inode;

}
