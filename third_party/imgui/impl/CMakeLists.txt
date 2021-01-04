add_library(imgui_impl SHARED
    include/imgui/impl/imgui_impl_glfw.h
    include/imgui/impl/imgui_impl_opengl3.h
    src/imgui_impl_glfw.cpp
    src/imgui_impl_opengl3.cpp)
target_include_directories(imgui_impl PUBLIC ../include/imgui/)
target_include_directories(imgui_impl PRIVATE include/imgui/impl/)
target_include_directories(imgui_impl PUBLIC include/)
target_link_libraries(imgui_impl PUBLIC glad glfw)
target_compile_definitions(imgui_impl PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
