include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(example example_test.cpp)
target_link_libraries(example gtest_main)
add_test(NAME example_test COMMAND example)


