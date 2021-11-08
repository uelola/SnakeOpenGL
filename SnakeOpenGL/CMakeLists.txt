cmake_minimum_required(VERSION 3.20)
project(SnakeOpenGL)

set(CMAKE_CXX_STANDARD 14)


# set up include dir
set(GLFW_H /usr/local/Cellar/glfw/3.3.4/include)
#set(GLM_H /usr/local/Cellar/glm/0.9.9.8/include)
include_directories( ${GLFW_H})
#include_directories(${PROJECT_SOURCE_DIR})

# set up library link
#set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.3.dylib)
link_libraries( ${OPENGL}  ${GLFW_LINK})

#the name (SnakeOpenGL) should be the same with target_link_libraries(SnakeOpenGL ...)
add_executable(SnakeOpenGL main.cpp game.cpp game.h)
#add_executable(Test test.cpp
#        common/shader.cpp
#        common/shader.hpp
#        )

# target link
if (APPLE)
   target_link_libraries(SnakeOpenGL "-framework OpenGL")
   target_link_libraries(SnakeOpenGL "-framework GLUT")
#   target_link_libraries(Snake "-framework OpenGL")
#   target_link_libraries(Snake "-framework GLUT")
endif()