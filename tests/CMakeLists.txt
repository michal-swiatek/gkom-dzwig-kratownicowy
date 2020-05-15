cmake_minimum_required(VERSION 3.15)
project(tests)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>")

# Test external libraries
add_subdirectory(external-libraries)