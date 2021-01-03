add_executable(imgui_renderer
    src/main.cpp)

target_link_libraries(imgui_renderer imgui glm_shared)

set(RESOURCE_FILES
    resource/fbo.fs
    resource/fbo.vs)
