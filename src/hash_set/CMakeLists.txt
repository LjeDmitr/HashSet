set(target_name hash_set)
set(HEADER_LIST "${CMAKE_SOURCE_DIR}/include/hash_set/hash_set.hpp")

add_library(${target_name} STATIC
  hash_set.cpp
  ${HEADER_LIST})

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)