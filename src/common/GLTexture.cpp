#include "GLTexture.hpp"

#include <iostream>
#include <string>

#include <stb_image.cpp>

namespace gl {
Texture::Texture(const char *filepath, int slot, int type) {
  stbi_set_flip_vertically_on_load(true);
  glGenTextures(1, &texture);
  unit = slot;
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load and generate the texture
  int width, height, nrChannels;
  unsigned char *data = stbi_load(filepath, &width, &height, &nrChannels, 0);
  if (data) {
    if (type == 0) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else if (type == 1) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
}

Texture::~Texture() {
  glDeleteTextures(1, &texture);
}

void Texture::Bind() {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::Unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
  glDeleteTextures(1, &texture);
}
} // namespace gl