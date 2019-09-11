cmake_minimum_required(VERSION 3.10)
project(tarefa_03)

set(OpenGlLinkers -lglut -lGLU -lGL -lm)

add_executable(tarefa_03 main.cpp)
target_link_libraries(tarefa_03 ${OpenGlLinkers}) # linking opengl libraries to the project
