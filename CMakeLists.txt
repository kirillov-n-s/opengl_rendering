cmake_minimum_required(VERSION 3.22)
project(laba3)

set(CMAKE_CXX_STANDARD 17)

add_executable(laba3 main.cpp
        stb_image/stb_image.cpp stb_image/stb_image.h
        cg/src/mesh.cpp cg/mesh.h
        cg/src/window.cpp cg/window.h
        cg/src/shader.cpp cg/shader.h cg/src/texture.cpp cg/texture.h cg/src/camera.cpp cg/camera.h cg/src/light.cpp cg/light.h cg/directions.h)

target_link_libraries(laba3 opengl32.lib)
target_link_libraries(laba3 glew32.lib)
target_link_libraries(laba3 glfw3.lib)
