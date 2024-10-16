#pragma once

#include <glad/gl.h>

#include <GLFW/glfw3.h>

namespace gl {
class GLBuffers {
public:
  GLBuffers();
  ~GLBuffers();

  void bind();
  void unBind();

private:
  unsigned int VBO, VAO, EBO;
};
} // namespace gl