include_directories("${CMAKE_SOURCE_DIR}/include")

set(PROJECT_INCLUDE_FILES "${CMAKE_SOURCE_DIR}/include/Window.h"
                          "${CMAKE_SOURCE_DIR}/include/Core.h"
                          "${CMAKE_SOURCE_DIR}/include/Cylinder.h"
                          "${CMAKE_SOURCE_DIR}/include/Shader.h"
                          "${CMAKE_SOURCE_DIR}/include/Transform.h"
                          "${CMAKE_SOURCE_DIR}/include/Camera.h"
                          "${CMAKE_SOURCE_DIR}/include/SkyBox.h"
                          "${CMAKE_SOURCE_DIR}/include/Material.h"
                          "${CMAKE_SOURCE_DIR}/include/PhongMaterial.h"
                          "${CMAKE_SOURCE_DIR}/include/LightHandler.h"
                          "${CMAKE_SOURCE_DIR}/include/Object.h"
                          "${CMAKE_SOURCE_DIR}/include/IObject.h"
                          "${CMAKE_SOURCE_DIR}/include/Model.h"
)

set(PROJECT_SRC_FILES "${CMAKE_SOURCE_DIR}/src/Window.cpp"
                      "${CMAKE_SOURCE_DIR}/src/Core.cpp"
                      "${CMAKE_SOURCE_DIR}/src/Cylinder.cpp"
                      "${CMAKE_SOURCE_DIR}/src/Shader.cpp"
                      "${CMAKE_SOURCE_DIR}/src/Camera.cpp"
                      "${CMAKE_SOURCE_DIR}/src/SkyBox.cpp"
                      "${CMAKE_SOURCE_DIR}/src/PhongMaterial.cpp"
                      "${CMAKE_SOURCE_DIR}/src/LightHandler.cpp"
                      "${CMAKE_SOURCE_DIR}/src/Object.cpp"
                      "${CMAKE_SOURCE_DIR}/src/Model.cpp"
)
