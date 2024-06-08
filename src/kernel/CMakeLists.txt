cmake_minimum_required(VERSION 3.5)
project(kernel LANGUAGES C ASM)

set(C_SOURCES
    src/main.c
    src/stdlib/stdio.c
    src/stdlib/memory.c
    src/stdlib/string.c
    src/stdlib/display.c
    src/stdlib/font.c
    src/stdlib/disk.c
    src/drivers/ATA.c
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
