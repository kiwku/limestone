#pragma once

#include <glad/gl.h>

#include <GLFW/glfw3.h>

class OpenGL {
public:
  OpenGL();
  ~OpenGL();
  void init();
  void render();

private:
  unsigned int VBO, VAO, EBO;
  unsigned int shaderProgram;
};
