project(bootloader LANGUAGES NONE)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binaries)
set(INTERMEDIATE_DIR ${CMAKE_SOURCE_DIR}/intermediate/bootloader)

file(MAKE_DIRECTORY ${INTERMEDIATE_DIR})

set(SOURCES
    ${SRC_DIR}/entry.asm
    )

foreach(SOURCE ${SOURCES})
  get_filename_component(SOURCE_NAME ${SOURCE} NAME_WE)
  add_custom_command(
      OUTPUT ${INTERMEDIATE_DIR}/${SOURCE_NAME}.bin
      COMMAND nasm -f bin -o ${INTERMEDIATE_DIR}/${SOURCE_NAME}.bin ${SOURCE}
      DEPENDS ${SOURCE}
      COMMENT "Assembling ${SOURCE_NAME}"
      )
  list(APPEND BINARY_FILES ${INTERMEDIATE_DIR}/${SOURCE_NAME}.bin)
endforeach()

add_custom_command(
    OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bootloader.bin
    COMMAND cat ${BINARY_FILES} > ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bootloader.bin
    DEPENDS ${BINARY_FILES}
    COMMENT "Concatenating binary files into bootloader.bin"
    )

add_custom_target(bootloader ALL DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bootloader.bin)
