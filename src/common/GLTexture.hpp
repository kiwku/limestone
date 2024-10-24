#pragma once

#include <glad/gl.h>

#include <GLFW/glfw3.h>

namespace gl {
class Texture {

public:
  Texture(const char *filepath, int slot, int type);
  ~Texture();

  void Bind();
  void Unbind();
  void Delete();

private:
  int unit;
  unsigned int texture;
};

} // namespace gl