#include "OpenGL.hpp"

#include <iostream>

namespace gl {

OpenGL::OpenGL() {
}

OpenGL::~OpenGL() {
}

void OpenGL::init() {
  // Nothing
}

void OpenGL::render() {
  shader->Activate();
  buffer->bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  buffer->unBind();
}

void OpenGL::setShader(Shader *shader) {
  this->shader = shader;
}

void OpenGL::setBuffer(GLBuffers *glBuffer) {
  buffer = glBuffer;
}

} // namespace gl