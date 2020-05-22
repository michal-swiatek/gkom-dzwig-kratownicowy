add_executable(test_glfw3 test_glfw3.cpp)
target_link_libraries(test_glfw3 ${OPENGL_LIBS})

add_executable(test_glm test_glm.cpp)
target_link_libraries(test_glm ${OPENGL_LIBS})
