cmake_minimum_required(VERSION 3.15)
project(dzwig-kratownicowy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(cmake/scripts/setup_libraries.cmake)
include(cmake/scripts/loadProjectFiles.cmake)

add_executable(main main.cpp ${PROJECT_INCLUDE_FILES} ${PROJECT_SRC_FILES})
target_link_libraries(main ${OPENGL_LIBS})

# Include tests
add_subdirectory(tests)
