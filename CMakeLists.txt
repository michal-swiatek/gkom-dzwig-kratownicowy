cmake_minimum_required(VERSION 3.15)
project(dzwig-kratownicowy)

set(CMAKE_CXX_STANDARD 14)

include(external-libraries/setup_libraries.cmake)

add_executable(main main.cpp)
target_link_libraries(main ${OPENGL_LIBS})

# Include tests
add_subdirectory(tests)
