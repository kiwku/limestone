#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <iostream>

#include "../common/Debug.hpp"
#include "../common/OpenGL.hpp"

GLFWwindow *window;

gl::OpenGL openGL;
Debug debug;

EMSCRIPTEN_KEEPALIVE
void main_loop() {
  glfwPollEvents();

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  openGL.render();

  glfwSwapBuffers(window);
}

EMSCRIPTEN_KEEPALIVE
int main(/*int argc, char *argv[]*/) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  window = glfwCreateWindow(800, 800, "test", NULL, NULL);
  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    return -1;
  }

  glfwSwapInterval(1);

  debug.Log("COS");
  debug.Error("COS2");

  gl::GLBuffers buffer;
  openGL.setBuffer(&buffer);

  gl::Shader shader("shaders/ESmain.vert", "shaders/ESmain.frag");
  openGL.setShader(&shader);

  openGL.init();

  fmt::print(fmt::fg(fmt::color::red) | fmt::emphasis::bold, "Hello World\n");

  emscripten_set_main_loop(main_loop, 0, 1);
  return 0;
}