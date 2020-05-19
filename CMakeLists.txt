cmake_minimum_required(VERSION 3.15)
project(dzwig-kratownicowy VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(cmake/scripts/setupLibraries.cmake)
include(cmake/scripts/includeProjectFiles.cmake)
include(cmake/scripts/includeResources.cmake)

configure_file("${CMAKE_SOURCE_DIR}/Configure.h.in" Configure.h)

add_executable(main main.cpp ${PROJECT_INCLUDE_FILES} ${PROJECT_SRC_FILES})
target_link_libraries(main ${OPENGL_LIBS})

target_include_directories(main PUBLIC "${CMAKE_BINARY_DIR}")   #   Include project version in main project

# Include tests
add_subdirectory(tests)



