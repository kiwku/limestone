#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <iostream>

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

GLFWwindow *window;

void main_loop() {
  glfwPollEvents();

  glClearColor(0.4f, 0.7f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers(window);
}

int main(/*int argc, char *argv[]*/) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(800, 800, "test", NULL, NULL);
  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    return -1;
  }

  glfwSwapInterval(1);

  fmt::print(fmt::fg(fmt::color::red) | fmt::emphasis::bold, "Hello World\n");

  emscripten_set_main_loop(main_loop, 0, 1);

  // Clean up and terminate
  glfwDestroyWindow(window);
  // glfwTerminate();
  return 0;
}