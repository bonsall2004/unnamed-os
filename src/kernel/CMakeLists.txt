cmake_minimum_required(VERSION 3.5)
project(kernel LANGUAGES CXX ASM)

set(C_SOURCES
    src/main.cpp
    src/libc/stdio.cpp
    src/libc/memory.cpp
    src/libc/string.cpp
    src/drivers/display.cpp
    src/misc/font.cpp
    src/drivers/disk.cpp
    src/drivers/ATA.cpp
    src/misc/idt.cpp
    src/kernel/scheduling/TaskScheduler.cpp
    )

set(ASM_SOURCES
    src/kernel/scheduling/context_switch.asm
    )

set(INCLUDE_DIRS
    includes/drivers
    includes/libc
    includes/stl
    includes/misc
    includes/kernel
    )

enable_language(ASM_NASM)

add_executable(kernel ${C_SOURCES} ${CXX_SOURCES} ${ASM_SOURCES})
target_include_directories(kernel PRIVATE ${INCLUDE_DIRS})
target_compile_options(kernel PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-mno-red-zone -fno-exceptions -fno-builtin -mgeneral-regs-only -fno-rtti -ffreestanding -fno-stack-protector -fno-stack-check -fpie -nostdlib -nostdinc -g >)
target_link_options(kernel PRIVATE -g -nostdlib -Wl,--build-id=none -z max-page-size=0x1000 -pie -T ${CMAKE_SOURCE_DIR}/src/linker_scripts/link-64-kernel.ld)
