cmake_minimum_required(VERSION 3.16)
project(ImguiFBO3D)

# configure
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# add our code
add_subdirectory(imgui_fbo_3d)

# add third party
add_subdirectory(third_party)
