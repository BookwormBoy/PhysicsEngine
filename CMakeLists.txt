cmake_minimum_required(VERSION 3.15)
project(Engine)

find_package(OpenGL REQUIRED)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0072 NEW)

# Add GLFW to the project
add_subdirectory(glfw)

# Add your source files
add_executable(engine src/main.cpp src/glad.c)

target_include_directories(engine PRIVATE include)

# Link GLFW to your project
target_link_libraries(engine glfw)

# Link OpenGL library (required for rendering)

target_link_libraries(engine OpenGL::GL)
