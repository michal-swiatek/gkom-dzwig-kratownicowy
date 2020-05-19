#Locate libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "GLFW3 include found at ${GLFW3_INCLUDE_DIR}")

#
# Build libraries from source files
#

# GLAD
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external-libraries/include")
set(GLAD_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external-libraries/src")
add_library(GLAD "${GLAD_SOURCE_DIR}/glad.c")

# Include libraries
include_directories("${GLFW3_INCLUDE_DIR}" "${GLAD_INCLUDE_DIR}")

# Linking
set(OPENGL_LIBS "${GLFW3_LIBRARY}" opengl32 GLAD)
