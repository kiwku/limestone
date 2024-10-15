#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl {

static std::string readShader(const char *filepath);

class Shader {
public:
  Shader(const char *vertexShaderPath, const char *fragmentShaderPath);

  void Activate();
  void Delete();

  void pasMat4(const glm::mat4 &mat4, const char *location);
  void pasVec3(const glm::vec3 &vec3, const char *location);

private:
  unsigned int shaderID;
};

} // namespace gl