include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Include directory of library
include_directories(${LIB_INCLUDE_DIR})

# Add executable of demo
add_executable(demo main.cpp Demo.cpp)
# Link demo to lin_sys_libary we created
target_link_libraries(demo  lin_sys_lib)




