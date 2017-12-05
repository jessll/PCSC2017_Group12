include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Include directory of library
include_directories(${LIB_INCLUDE_DIR})

# Add executable of tests
add_executable(BasicTests TestBaseClasses.cpp  TestSolverClasses.cpp)

# Link to lin_sys_libary we created and g_test
target_link_libraries(BasicTests  gtest_main lin_sys_lib)

# Is this line necessary?
add_test(NAME BasicTests COMMAND runTests)


