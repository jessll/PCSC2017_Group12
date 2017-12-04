include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main Matrix.cpp Vector.cpp main.cpp LinSysSolver.hpp LinSysSolver.cpp IterativeSolver.hpp IterativeSolver.cpp CGSolver.hpp CGSolver.cpp JacSolver.hpp JacSolver.cpp RichSolver.hpp RichSolver.cpp GSSolver.cpp GSSolver.hpp)


