include_directories("${CMAKE_SOURCE_DIR}/include")

set(PROJECT_INCLUDE_FILES "${CMAKE_SOURCE_DIR}/include/Window.h"
                          "${CMAKE_SOURCE_DIR}/include/Core.h"
                          "${CMAKE_SOURCE_DIR}/include/Cylinder.h"
                          "${CMAKE_SOURCE_DIR}/include/Shader.h"
)

set(PROJECT_SRC_FILES "${CMAKE_SOURCE_DIR}/src/Window.cpp"
                      "${CMAKE_SOURCE_DIR}/src/Core.cpp"
                      "${CMAKE_SOURCE_DIR}/src/Cylinder.cpp"
                      "${CMAKE_SOURCE_DIR}/src/Shader.cpp"
)
