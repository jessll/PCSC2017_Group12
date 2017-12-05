include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(LIB_INCLUDE_DIR ${LIB_INCLUDE_DIR} PARENT_SCOPE)

if(TARGET lin_sys_lib)

    message("lin_sys_lib is already defined")

else()

    include_directories(${SHARED_LIB_INCLUDE_DIR})
    set (LIB_SOURCE_FILES Matrix.cpp Vector.cpp  LinSysSolver.cpp IterativeSolver.cpp CGSolver.cpp
            JacSolver.cpp RichSolver.cpp GSSolver.cpp)
    add_library(lin_sys_lib  SHARED ${LIB_SOURCE_FILES})

endif()






