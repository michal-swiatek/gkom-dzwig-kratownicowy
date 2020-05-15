cmake_minimum_required(VERSION 3.15)
project(dzwig-kratownicowy)

set(CMAKE_CXX_STANDARD 14)

add_executable(hello-world main.cpp)
target_link_libraries(hello-world ${OPENGL_LIBS})
