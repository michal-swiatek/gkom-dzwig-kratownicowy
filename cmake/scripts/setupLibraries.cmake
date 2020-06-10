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
set(SOIL_LIBRARY "${CMAKE_SOURCE_DIR}/external-libraries/lib/SOIL.lib")

# GLEW
set(GLEW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external-libraries/include")
set(GLEW_LIBRARY  "${CMAKE_SOURCE_DIR}/external-libraries/lib/glew32.lib" "${CMAKE_SOURCE_DIR}/external-libraries/lib/glew32s.lib")

# Include libraries
include_directories("${SOIL_INCLUDE_DIR}" "${GLFW3_INCLUDE_DIR}" "${GLM_INCLUDE_DIRS}" "${GLEW_INCLUDE_DIR}")

# Linking
set(OPENGL_LIBS "${GLEW_LIBRARY}" "${GLFW3_LIBRARY}" "${SOIL_LIBRARY}" opengl32)
