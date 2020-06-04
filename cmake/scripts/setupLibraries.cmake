#Locate libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "GLFW3 include found at ${GLFW3_INCLUDE_DIR}")

# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM include found at ${GLM_INCLUDE_DIRS}")

# SOIL
set(SOIL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external-libraries/include")
set(SOIL_LIBRARY "${CMAKE_SOURCE_DIR}/external-libraries/lib")

#
# Build libraries from source files
#

# GLAD
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external-libraries/include")
set(GLAD_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external-libraries/src")
add_library(GLAD "${GLAD_SOURCE_DIR}/glad.c")

# Include libraries
include_directories("${SOIL_INCLUDE_DIR}" "${GLFW3_INCLUDE_DIR}" "${GLAD_INCLUDE_DIR}" "${GLM_INCLUDE_DIRS}")

# Linking
set(OPENGL_LIBS "${GLFW3_LIBRARY}" SOIL opengl32 GLAD)
