add_executable(imgui_renderer
    src/main.cpp)

target_link_libraries(imgui_renderer imgui glm_shared)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "${CMAKE_CURRENT_BINARY_DIR}/assets"
    COMMENT "Copy assets to build output"
    VERBATIM)
