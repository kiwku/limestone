#include <iostream>

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

int main(/*int argc, char *argv[]*/) {

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

  fmt::print(fmt::fg(fmt::color::red) | fmt::emphasis::bold, "Hello World\n");
  return 0;
}
