include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(BasicTests TestBaseClasses.cpp ../src/Matrix.cpp ../src/Vector.cpp TestSolverClasses.cpp
        ../src/CGSolver.cpp ../src/IterativeSolver.cpp ../src/LinSysSolver.cpp ../src/RichSolver.cpp
        ../src/JacSolver.cpp ../src/GSSolver.cpp)
target_link_libraries(BasicTests  gtest_main)
add_test(NAME BasicTests COMMAND runTests)


