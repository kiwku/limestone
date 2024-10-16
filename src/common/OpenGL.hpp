
#pragma once

#include "GLBuffers.hpp"
#include "GLShaderLoader.hpp"
namespace gl {
class OpenGL {
public:
  OpenGL();
  ~OpenGL();
  void init();
  void render();

  void setShader(Shader *shader);
  void setBuffer(GLBuffers *glBuffer);

private:
  Shader *shader;
  GLBuffers *buffer;
  unsigned int VBO, VAO, EBO;
};
} // namespace gl
