cmake_minimum_required(VERSION 3.5)
project(kernel LANGUAGES CXX ASM)

set(C_SOURCES
    src/main.cpp
    src/stdlib/stdio.cpp
    src/stdlib/memory.cpp
    src/stdlib/string.cpp
    src/stdlib/display.cpp
    src/stdlib/font.cpp
    src/stdlib/disk.cpp
    src/drivers/ATA.cpp
    )

set(ASM_SOURCES

    )

set(CXX_SOURCES
    )

enable_language(ASM_NASM)

add_executable(kernel ${C_SOURCES} ${CXX_SOURCES} ${ASM_SOURCES})

target_include_directories(kernel PRIVATE ./includes)

target_compile_options(kernel PRIVATE -fno-builtin -ffreestanding -fno-stack-protector -fno-stack-check -fpie -mno-red-zone -nostdlib -nostdinc)
target_link_options(kernel PRIVATE -nostdlib -z max-page-size=0x1000 -pie -T ${CMAKE_SOURCE_DIR}/src/linker_scripts/link-64-kernel.ld)
