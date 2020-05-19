# Define command for copying resources
set(RESOURCES_COPY_COMMAND copy_directory)
set(RESOURCES_USE_SYMLINK False CACHE STRING "Copy resources by symlink (symlink might require admin privileges to work) (True or False)" FORCE)

if(RESOURCES_USE_SYMLINK STREQUAL "True")
    set(RESOURCES_COPY_COMMAND create_symlink)
endif()

# Include shaders and resource files
include_directories("${CMAKE_SOURCE_DIR}/shaders")
