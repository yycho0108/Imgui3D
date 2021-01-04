add_library(imgui SHARED
    include/imgui/imconfig.h
    include/imgui/imgui.h
    include/imgui/imgui_internal.h
    include/imgui/imstb_rectpack.h
    include/imgui/imstb_textedit.h
    include/imgui/imstb_truetype.h
    src/imgui.cpp
    src/imgui_draw.cpp
    src/imgui_widgets.cpp
    src/imgui_tables.cpp
    )
target_link_libraries(imgui PUBLIC imgui_impl)
target_include_directories(imgui PRIVATE include/imgui/)
target_include_directories(imgui PUBLIC include/)

add_subdirectory(impl)
add_subdirectory(example)
