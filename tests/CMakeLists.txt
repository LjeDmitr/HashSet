set(target_name hash_set_test)

add_executable(${target_name} hash_set_test.cpp)

include(GoogleTest)
include(CompileOptions)
set_compile_options(${target_name})

target_sources(
  ${target_name}
  PRIVATE
  hash_set_test.cpp
)

include_directories("${CMAKE_SOURCE_DIR}/include/hash_set")

target_link_libraries(
  ${target_name}
  PRIVATE
    gtest_main
    gtest
    hash_set
)

add_test(NAME ${target_name} COMMAND ${target_name})