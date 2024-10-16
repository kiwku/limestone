
#pragma once

#include "GLShaderLoader.hpp"

#include <glad/gl.h>

#include <GLFW/glfw3.h>
namespace gl {
class OpenGL {
public:
  OpenGL();
  ~OpenGL();
  void init();
  void render();

  void setShader(Shader *shader);

private:
  Shader *shader;
  unsigned int VBO, VAO, EBO;
};
} // namespace gl
