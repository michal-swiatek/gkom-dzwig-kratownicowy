#Locate libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# OpenGL
if(WIN32)
    set(OPENGL_LIBS glfw3 opengl32)
elseif(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
    find_package(OpenGL REQUIRED)
    add_definitions(${OPENGL_DEFINITIONS})
    find_package(X11 REQUIRED)
    # note that the order is important for setting the libs
    # use pkg-config --libs $(pkg-config --print-requires --print-requires-private glfw3) in a terminal to confirm
    set(OPENGL_LIBS X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread)
    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
else()
    set(OPENGL_LIBS )
endif(WIN32)

# GLFW
find_package(GLFW3)
message(STATUS "GLFW3 include found at ${GLFW3_INCLUDE_DIR}")

# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM include found at ${GLM_INCLUDE_DIRS}")

# GLEW
find_package(GLEW REQUIRED)
message(STATUS "GLEW include found at ${GLEW_INCLUDE_DIRS}")

# SOIL
set(SOIL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external-libraries/include")
set(SOIL_LIBRARY "${CMAKE_SOURCE_DIR}/external-libraries/lib")


# Include libraries
include_directories("${SOIL_INCLUDE_DIR}" "${GLFW3_INCLUDE_DIR}" "${GLM_INCLUDE_DIRS}" "${GLEW_INCLUDE_DIR}")

# Linking
set(OPENGL_LIBS glfw3 GLEW SOIL "${OPENGL_LIBS}")