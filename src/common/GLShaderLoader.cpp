#include "GLShaderLoader.hpp"

namespace gl {

static std::string readShader(const char *filepath) {
  std::ifstream in(filepath, std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  throw(errno);
}

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {
  std::string vertexShaderCode = readShader(vertexShaderPath);
  std::string fragmentShaderCode = readShader(fragmentShaderPath);

  const char *vertexShaderSource = vertexShaderCode.c_str();
  const char *fragmentShaderSource = fragmentShaderCode.c_str();

  int success;
  char infoLog[512];

  // Vertex shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Fragment shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Combined Shaders
  shaderID = glCreateProgram();

  glAttachShader(shaderID, vertexShader);
  glAttachShader(shaderID, fragmentShader);
  glLinkProgram(shaderID);

  glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
void Shader::Activate() {
  glUseProgram(shaderID);
}

void Shader::Delete() {
  glUseProgram(shaderID);
}

void Shader::pasMat4(const glm::mat4 &mat4, const char *location) {
  unsigned int transformLoc = glGetUniformLocation(shaderID, location);
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &mat4[0][0]);
}

void Shader::pasVec3(const glm::vec3 &vec3, const char *location) {
  unsigned int transformLoc = glGetUniformLocation(shaderID, location);
  glUniform3fv(transformLoc, 1, &vec3[0]);
}

}