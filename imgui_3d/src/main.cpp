#include "imgui/imgui.h"
#include "imgui/impl/imgui_impl_glfw.h"
#include "imgui/impl/imgui_impl_opengl3.h"

#include <cstdio>
#include <cstdlib>
#include <memory>

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtx/string_cast.hpp>

#include <glad/glad.h>  // Initialize with gladLoadGL()

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

// Temporary ...
// #include <learnopengl/filesystem.h>
#include "camera.h"
#include "shader_m.h"

static void glfw_error_callback(int error, const char* description) {
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void CHECK_FRAMEBUFFER_STATUS() {
  GLenum status;
  status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
  switch (status) {
    case GL_FRAMEBUFFER_COMPLETE:
      break;

    case GL_FRAMEBUFFER_UNSUPPORTED:
      /* choose different formats */
      break;

    default:
      /* programming error; will fail on all hardware */
      fputs("Framebuffer Error\n", stderr);
      exit(-1);
  }
}

void SetupGeometries(unsigned int* const cubeVAO, unsigned int* const cubeVBO,
                     unsigned int* const planeVAO,
                     unsigned int* const planeVBO) {
  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float cubeVertices[] = {
      // positions          // texture Coords
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};
  float planeVertices[] = {
      // positions          // texture Coords
      5.0f, -0.5f, 5.0f,  2.0f,  0.0f,  -5.0f, -0.5f, 5.0f,
      0.0f, 0.0f,  -5.0f, -0.5f, -5.0f, 0.0f,  2.0f,

      5.0f, -0.5f, 5.0f,  2.0f,  0.0f,  -5.0f, -0.5f, -5.0f,
      0.0f, 2.0f,  5.0f,  -0.5f, -5.0f, 2.0f,  2.0f};

  // cube VAO
  glBindVertexArray(*cubeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, *cubeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(3 * sizeof(float)));

  // plane VAO
  glBindVertexArray(*planeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, *planeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(3 * sizeof(float)));
}

struct ImguiRenderer {
  explicit ImguiRenderer(const int width, const int height)
      : width_(width),
        height_(height),
        camera_(glm::vec3(0.0f, 0.0f, 3.0f)),
        shader_("assets/5.1.framebuffers.vs", "assets/5.1.framebuffers.fs") {
    // camera.Zoom = 45;
    Allocate();
    SetupFbo();
    SetupGeometries(&cube_vao_, &cube_vbo_, &plane_vao_, &plane_vbo_);
  }

  ~ImguiRenderer() { Deallocate(); }

  void SetupFbo() {
    // Bind to fbo
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

    // Texture
    glBindTexture(GL_TEXTURE_2D, texture_);

    // Configure texture (color) buffer
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           texture_, 0);

    // Configure render buffer
    glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_,
                          height_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, rbo_);

    // Validation
    CHECK_FRAMEBUFFER_STATUS();

    // Unbind everything for cleanup of context state.
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void Allocate() {
    // Gen
    glGenFramebuffers(1, &fbo_);
    glGenTextures(1, &texture_);
    glGenRenderbuffers(1, &rbo_);

    glGenVertexArrays(1, &cube_vao_);
    glGenBuffers(1, &cube_vbo_);

    glGenVertexArrays(1, &plane_vao_);
    glGenBuffers(1, &plane_vbo_);
  }

  void Deallocate() {
    if (cube_vao_) {
      glDeleteVertexArrays(1, &cube_vao_);
      cube_vao_ = 0;
    }
    if (plane_vao_) {
      glDeleteVertexArrays(1, &plane_vao_);
      plane_vao_ = 0;
    }

    if (cube_vbo_) {
      glDeleteBuffers(1, &cube_vbo_);
      cube_vbo_ = 0;
    }

    if (plane_vbo_) {
      glDeleteBuffers(1, &plane_vbo_);
      plane_vbo_ = 0;
    }

    if (rbo_) {
      glDeleteRenderbuffers(1, &rbo_);
      rbo_ = 0;
    }
    if (texture_) {
      glDeleteTextures(1, &texture_);
    }

    if (fbo_) {
      glDeleteFramebuffers(1, &fbo_);
    }
  }

  void Draw(const float* const vertices, const int num_vertices,
            const float* const indices, const int num_indices,
            const GLenum mode) {
    // Generate buffers
    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    if (num_indices > 0) {
      glGenBuffers(1, &ebo);
    }

    // Bind and send to device
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), vertices,
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    // glVertexAttribPointer(
  }

  void Render() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);

    glViewport(0, 0, width_, height_);

    // Clear
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_.use();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera_.GetViewMatrix();
    glm::mat4 projection =
        glm::perspective(glm::radians(camera_.Zoom),
                         (float)width_ / (float)height_, 0.1f, 100.0f);

    shader_.setMat4("view", view);
    shader_.setMat4("projection", projection);
    shader_.setFloat("point_size", 10.0F);

    // Draw cubes.
    glBindVertexArray(cube_vao_);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    shader_.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawArrays(GL_POINTS, 0, 36);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    shader_.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawArrays(GL_POINTS, 0, 36);

    // floor
    glBindVertexArray(plane_vao_);
    shader_.setMat4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // reset VAO
    glBindVertexArray(0);
    // reset FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
  const GLuint& GetTexture() const { return texture_; }

 public:
  // Config
  int width_;
  int height_;
  GLuint fbo_;
  GLuint texture_;
  GLuint rbo_;

  // Geometry
  unsigned int cube_vao_{0};
  unsigned int cube_vbo_{0};
  unsigned int plane_vao_{0};
  unsigned int plane_vbo_{0};

  // Camera
  Camera camera_;

  // Shader
  Shader shader_;
};

struct ImguiViewerApp {
  explicit ImguiViewerApp() {}
  ~ImguiViewerApp() {
    // Cleanup renderer prior to destroying context.
    renderer = nullptr;

    // Cleanup IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Cleanup GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
  }
  bool SetupGL() {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
      return false;
    }

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
    // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only

    // Create window with graphics context
    window = glfwCreateWindow(1280, 720, "IMGUI VIEWER", NULL, NULL);
    if (window == NULL) {
      return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    // Initialize OpenGL loader.
    bool err = gladLoadGL() == 0;
    if (err) {
      fprintf(stderr, "Failed to initialize OpenGL loader!\n");
      return false;
    }
    return true;
  }

  bool SetupImgui() {
    const char* glsl_version = "#version 130";

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= io.ConfigWindowsMoveFromTitleBarOnly;
    // ImGuiIO& io = ImGui::GetIO();
    // (void)io;
    // io.ConfigFlags |= io.ConfigWindowsMoveFromTitleBarOnly;
    // io.ConfigFlags |= io.WantCaptureMouse;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
  }

  bool SetupRenderer() {
    renderer = std::make_shared<ImguiRenderer>(512, 512);
    return true;
  }

  void Setup() {
    if (!SetupGL()) {
      return;
    }
    if (!SetupImgui()) {
      return;
    }
    if (!SetupRenderer()) {
      return;
    }
  }

  void Step() {
    // Configure io here?
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= io.ConfigWindowsMoveFromTitleBarOnly;

    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
    // tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to
    // your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
    // data to your main application. Generally you may always pass all inputs
    // to dear imgui, and hide them from your application based on those two
    // flags.
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
      ImGui::Begin("Scene");  //
      // , nullptr, ImGuiWindowFlags_NoNavInputs);

      // Render scene to FBO.
      renderer->Render();
      const GLuint& tex = renderer->GetTexture();

      const ImVec2 win_size = ImVec2{ImGui::GetWindowContentRegionMax().x -
                                         ImGui::GetWindowContentRegionMin().x,
                                     ImGui::GetWindowContentRegionMax().y -
                                         ImGui::GetWindowContentRegionMin().y};
      ImGui::ImageButton(reinterpret_cast<ImTextureID>(tex),
                         ImVec2{1.0F * win_size.x, 1.0F * win_size.y},
                         ImVec2(0, 1), ImVec2(1, 0));
      // std::cout << io.WantCaptureMouse << std::endl;

      // Deal with controls.
      const bool is_hovered = ImGui::IsItemHovered();  // Hovered
      const bool is_active = ImGui::IsItemActive();    // Held

      // Process mouse events.
      if (ImGui::IsMouseDown(ImGuiMouseButton_Middle)) {
        if (!mouse_down) {
          // mouse_prev = ImGui::GetIO().MousePosGetCursorPos();
          mouse_prev = io.MousePos;
        }
        mouse_down = true;
      }

      if (ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 1.0F) && mouse_down) {
        // auto& io = ImGui::GetIO();
        const ImVec2& mouse_curr = io.MousePos;
        const ImVec2 delta{mouse_curr.x - mouse_prev.x,
                           mouse_curr.y - mouse_prev.y};
        renderer->camera_.ProcessMouseMovement(delta.x, -delta.y);
        mouse_prev = mouse_curr;
      }

      if (ImGui::IsMouseReleased(ImGuiMouseButton_Middle)) {
        mouse_down = false;
      }

      ImGui::End();
    }

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  void Spin() {
    while (!glfwWindowShouldClose(window)) {
      Step();
    }
  }

 private:
  // Handles
  GLFWwindow* window;
  std::shared_ptr<ImguiRenderer> renderer;

  // Settings
  ImVec4 clear_color{0.45f, 0.55f, 0.60f, 1.00f};

  // App state
  bool mouse_down{false};
  ImVec2 mouse_prev;
};

int main(int, char**) {
  ImguiViewerApp viewer;
  viewer.Setup();
  viewer.Spin();
}
