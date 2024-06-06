project(kernel LANGUAGES NONE)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries)
set(INTERMEDIATE_DIR ${CMAKE_SOURCE_DIR}/intermediate/kernel)

file(MAKE_DIRECTORY ${INTERMEDIATE_DIR})

set(ASM_SOURCES
#    ${SRC_DIR}/entry.asm
#    ${SRC_DIR}/test.asm
    )

set(C_SOURCES
    ${SRC_DIR}/main.c
    )

# Assemble assembly sources
foreach(SOURCE ${ASM_SOURCES})
  get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
  add_custom_command(
      OUTPUT ${INTERMEDIATE_DIR}/${SOURCE_NAME}.bin
      COMMAND nasm -f bin ${SOURCE} -o ${INTERMEDIATE_DIR}/${SOURCE_NAME}.bin
      DEPENDS ${SOURCE}
      COMMENT "Assembling ${SOURCE_NAME}"
      )
  list(APPEND BINARY_FILES ${INTERMEDIATE_DIR}/${SOURCE_NAME}.bin)
endforeach()

# Compile C sources
foreach(SOURCE ${C_SOURCES})
  get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
  add_custom_command(
      OUTPUT ${INTERMEDIATE_DIR}/${SOURCE_NAME}.o
      COMMAND gcc -c ${SOURCE} -nostdlib -o ${INTERMEDIATE_DIR}/${SOURCE_NAME}.o
      DEPENDS ${SOURCE}
      COMMENT "Compiling ${SOURCE_NAME}"
      )
  list(APPEND BINARY_FILES ${INTERMEDIATE_DIR}/${SOURCE_NAME}.o)
endforeach()

# Concatenate binary files into kernel.bin
add_custom_command(
    OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin
    COMMAND cat ${BINARY_FILES} > ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin
    DEPENDS ${BINARY_FILES}
    COMMENT "Concatenating binary files into kernel.bin"
    )

# Define custom target for building kernel
add_custom_target(kernel ALL DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel.bin)
