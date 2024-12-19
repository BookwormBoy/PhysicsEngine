cmake_minimum_required(VERSION 3.15)
project(Engine)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add GLFW to the project
add_subdirectory(glfw)

# Add your source files
add_executable(engine src/main.cpp)

# Link GLFW to your project
target_link_libraries(engine glfw)

# Link OpenGL library (required for rendering)
find_package(OpenGL REQUIRED)
target_link_libraries(engine OpenGL::GL)
