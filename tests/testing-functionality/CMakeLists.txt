add_executable(display_cylinder display_cylinder.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES} ../../src/SkyBox.cpp ../../include/SkyBox.h)
target_link_libraries(display_cylinder ${OPENGL_LIBS})

# Adding shaders to build and executable directory
COPY_RESOURCES(display_cylinder ${RESOURCES_COPY_COMMAND})

# Set working directory for MS Visual Studio
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(display_cylinder PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()