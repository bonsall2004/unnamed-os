#!/bin/bash

set -e

IMAGE_FILE="bootable.hdd"

mkdir -p intermediate/debug/x64

cd intermediate/debug/x64

cmake -DCMAKE_BUILD_TYPE=Debug -G "Ninja" ../../../
ninja all

cd ../../../
qemu-system-x86-64 -drive format=raw,file=bootable.hdd -m 2G --no-reboot --no-shutdown --monitor stdio