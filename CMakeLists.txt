cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_COMPILER g++)

project(
  HashSet
  VERSION 1.0
  LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_program(CLANG_TIDY_EXE NAMES clang-tidy-14 clang-tidy)
if (NOT CLANG_TIDY_EXE)
  message(WARNING "clang-tidy not found")
else()
  execute_process(
    COMMAND ${CLANG_TIDY_EXE} --version
    OUTPUT_VARIABLE CLANG_TIDY_VERSION)
  message("clang-tidy found:\n" ${CLANG_TIDY_VERSION})
endif()

find_program(CLANG_FORMAT_EXE "clang-format-14")

if(CLANG_FORMAT_EXE)
  message("clang-format-14 found: ${CLANG_FORMAT_EXE}")
else()
  message("clang-format-14 not found.")
endif()

set(FORMATTED_FILES
    ${PROJECT_SOURCE_DIR}/tests/*.cpp
    ${PROJECT_SOURCE_DIR}/src/**/*.cpp
    ${PROJECT_SOURCE_DIR}/include/**/*.hpp
)

add_custom_target(format
    COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${FORMATTED_FILES}
    COMMENT "Formatting source files..."
)

enable_testing()

add_subdirectory(tests)
add_subdirectory(external)
add_subdirectory(src)