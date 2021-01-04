# Imgui3D

FBO based Imgui 3D renderer example.

Part of the code has been adapted from [LearnOpenGL](https://github.com/JoeyDeVries/LearnOpenGL).

## Directory structure

Currently, the directory structure is something like the following:

```
.
├── build [10 entries exceeds filelimit, not opening dir]
├── CMakeLists.txt
├── compile_commands.json -> build/compile_commands.json
├── imgui_fbo_3d
│   ├── CMakeLists.txt
│   ├── include
│   │   └── imgui_renderer
│   └── src
│       ├── camera.h
│       ├── main.cpp
│       └── shader_m.h
├── README.md
└── third_party
    ├── CMakeLists.txt
    ├── glad
    │   ├── CMakeLists.txt
    │   ├── glad.c
    │   └── include
    │       └── glad
    │           └── glad.h
    ├── glm [29 entries exceeds filelimit, not opening dir]
    ├── imgui
    │   ├── CMakeLists.txt
    │   ├── example
    │   │   ├── CMakeLists.txt
    │   │   └── src
    │   │       └── main.cpp
    │   ├── impl
    │   │   ├── CMakeLists.txt
    │   │   ├── include
    │   │   │   └── imgui
    │   │   │       └── impl
    │   │   │           ├── imgui_impl_glfw.h
    │   │   │           └── imgui_impl_opengl3.h
    │   │   └── src
    │   │       ├── imgui_impl_glfw.cpp
    │   │       └── imgui_impl_opengl3.cpp
    │   ├── include
    │   │   └── imgui
    │   │       ├── imconfig.h
    │   │       ├── imgui.h
    │   │       ├── imgui_internal.h
    │   │       ├── imstb_rectpack.h
    │   │       ├── imstb_textedit.h
    │   │       └── imstb_truetype.h
    │   └── src
    │       ├── imgui.cpp
    │       ├── imgui_draw.cpp
    │       ├── imgui_tables.cpp
    │       └── imgui_widgets.cpp
    └── README.md
```
