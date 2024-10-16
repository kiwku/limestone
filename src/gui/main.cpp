#include <iostream>

#include "../common/GLShaderLoader.hpp"
#include "../common/OpenGL.hpp"

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

int main(/*int argc, char *argv[]*/) {
  if (glfwPlatformSupported(GLFW_PLATFORM_WAYLAND)) {
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
    fmt::println("Wayland Support");
  } else {
    fmt::println("No Wayland Support");
  }
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 800, "test", NULL, NULL);
  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    return -1;
  }

  glfwSwapInterval(1);

  gl::OpenGL openGL;

  gl::Shader shader(SHADER_PATH "COmain.vert", SHADER_PATH "COmain.frag");
  openGL.setShader(&shader);

  openGL.init();

  fmt::print(fmt::fg(fmt::color::red) | fmt::emphasis::bold, "Hello World\n");

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    openGL.render();

    glfwSwapBuffers(window);
  }

  // Clean up and terminate
  glfwDestroyWindow(window);
  // glfwTerminate();
  return 0;
}