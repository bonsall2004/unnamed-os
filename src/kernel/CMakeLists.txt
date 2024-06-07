cmake_minimum_required(VERSION 3.5)
project(kernel LANGUAGES NONE)

set(C_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    )

set(ASM_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/entry.asm
    )

# Create output directory
set(INTERMEDIATE_DIR ${CMAKE_SOURCE_DIR}/intermediate/kernel)
if(NOT INTERMEDIATE_DIR)
  set(INTERMEDIATE_DIR ${CMAKE_BINARY_DIR}/bin)
endif()
file(MAKE_DIRECTORY ${INTERMEDIATE_DIR})

# Assemble ASM sources
set(ASM_OBJECTS)
foreach(ASM_FILE IN LISTS ASM_SOURCES)
  get_filename_component(ASM_NAME ${ASM_FILE} NAME_WE)
  set(ASM_OBJECT ${INTERMEDIATE_DIR}/${ASM_NAME}.o)
  add_custom_command(
      OUTPUT ${ASM_OBJECT}
      COMMAND nasm -f elf64 -o ${ASM_OBJECT} ${ASM_FILE}
      DEPENDS ${ASM_FILE}
      COMMENT "Assembling ${ASM_FILE}"
      )
  list(APPEND ASM_OBJECTS ${ASM_OBJECT})
endforeach()

# Compile C sources
set(C_OBJECTS)
foreach(C_FILE IN LISTS C_SOURCES)
  get_filename_component(C_NAME ${C_FILE} NAME_WE)
  set(C_OBJECT ${INTERMEDIATE_DIR}/${C_NAME}.o)
  add_custom_command(
      OUTPUT ${C_OBJECT}
      COMMAND gcc -mcmodel=large -ffreestanding -c -o ${C_OBJECT} ${C_FILE} -nostdlib -fno-asynchronous-unwind-tables -fno-unwind-tables
      DEPENDS ${C_FILE}
      COMMENT "Compiling ${C_FILE}"
      )
  list(APPEND C_OBJECTS ${C_OBJECT})
endforeach()

# Link all objects into kernel.bin
add_custom_command(
    OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin
    COMMAND ld --nmagic -o ${INTERMEDIATE_DIR}/kernel.elf -T ${CMAKE_SOURCE_DIR}/src/linker_scripts/link-64-kernel.ld ${ASM_OBJECTS} ${C_OBJECTS}
    COMMAND objcopy -O binary -j .init -j .text -j .rodata -j .data ${INTERMEDIATE_DIR}/kernel.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin
    DEPENDS ${ASM_OBJECTS} ${C_OBJECTS}
    COMMENT "Linking kernel.bin"
    )

add_custom_target(kernel ALL DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin)