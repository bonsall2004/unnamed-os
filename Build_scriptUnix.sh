#!/bin/bash

set -e

# Define variables
BINARIES_FOLDER="binaries"
BOOTLOADER_FILE="$BINARIES_FOLDER/bootloader/stage1.bin"
IMAGE_FILE="bootable_disk.img"

mkdir -p intermediate/debug/x64

cd intermediate/debug/x64

cmake -DCMAKE_BUILD_TYPE=Debug -G "Ninja" ../../../
ninja all
