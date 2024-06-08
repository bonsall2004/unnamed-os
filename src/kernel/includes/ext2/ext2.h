/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#pragma once
#include "../stdint.h"

typedef struct {
  uint32_t total_inodes;
  uint32_t total_blocks;
  uint32_t reserved_blocks;
  uint32_t free_blocks;
  uint32_t free_inodes;
  uint32_t superblock_block_num;
  uint32_t log_block_size;
  uint32_t log_frag_size;
  uint32_t blocks_per_group;
  uint32_t frags_per_group;
  uint32_t inodes_per_group;
  uint32_t mount_time;
  uint32_t write_time;
  uint16_t mounts_since_last_check;
  uint16_t mounts_allowed_before_check;
  uint16_t signature;
  uint16_t fs_state;
  uint16_t error_handling;
  uint16_t minor_version;
  uint32_t last_fsck_time;
  uint32_t fsck_interval;
  uint32_t os_id;
  uint32_t major_version;
  uint16_t reserved_uid;
  uint16_t reserved_gid;
  uint32_t first_inode;
  uint16_t inode_size;
  uint16_t block_group_number;
  uint32_t feature_compatibility;
  uint32_t feature_incompat;
  uint32_t feature_ro_compat;
  uint8_t  uuid[16];
  char     volume_name[16];
  char     last_mounted[64];
  uint32_t algorithm_usage_bitmap;
  uint8_t  prealloc_blocks;
  uint8_t  prealloc_dir_blocks;
  uint16_t padding;
  uint8_t  journal_uuid[16];
  uint32_t journal_inode;
  uint32_t journal_dev;
  uint32_t last_orphan;
  uint32_t hash_seed[4];
  uint8_t  def_hash_version;
  uint8_t  reserved_char_pad;
  uint16_t reserved_word_pad;
  uint32_t default_mount_options;
  uint32_t first_meta_bg;
  uint32_t reserved[190];
} ext2_superblock_t;

typedef struct {
  uint32_t block_bitmap;
  uint32_t inode_bitmap;
  uint32_t inode_table;
  uint16_t free_blocks_count;
  uint16_t free_inodes_count;
  uint16_t used_dirs_count;
  uint16_t pad;
  uint8_t  reserved[12];
} ext2_group_desc_t;

typedef struct {
  uint16_t mode;
  uint16_t uid;
  uint32_t size;
  uint32_t atime;
  uint32_t ctime;
  uint32_t mtime;
  uint32_t dtime;
  uint16_t gid;
  uint16_t links_count;
  uint32_t blocks;
  uint32_t flags;
  uint32_t osd1;
  uint32_t block[15];
  uint32_t generation;
  uint32_t file_acl;
  uint32_t dir_acl;
  uint32_t faddr;
  uint8_t  osd2[12];
} ext2_inode_t;

typedef struct {
  uint32_t inode;
  uint16_t rec_len;
  uint8_t  name_len;
  uint8_t  file_type;
  char     name[];
} ext2_dir_entry_t;
