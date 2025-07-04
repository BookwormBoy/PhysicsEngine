cmake_minimum_required(VERSION 3.15)
project(Engine)

find_package(OpenGL REQUIRED)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0072 NEW)

# Add GLFW to the project
add_subdirectory(glfw)

# Add your source files
add_executable(engine 
                src/cloth_main.cpp 
                src/glad.c 
                src/renderer.cpp 
                src/vertexBuffer.cpp 
                src/indexBuffer.cpp 
                src/vertexArray.cpp 
                src/vertexBufferLayout.cpp 
                src/shader.cpp 
                src/stb_image.cpp 
                src/texture.cpp 
                src/camera.cpp
                src/shape.cpp
                src/cube.cpp
                src/particle.cpp
                src/core.cpp
                src/pcontact.cpp
                src/plinks.cpp
                src/cloth.cpp)

target_include_directories(engine PRIVATE include)

# Link GLFW to your project
target_link_libraries(engine glfw)

# Link OpenGL library (required for rendering)

target_link_libraries(engine OpenGL::GL)
