#include <stdio.h>
#include <iostream>
#include <assert.h>
#include "Shader.h"

void Shader::init(const std::string &_name, const std::string &_vertex, const std::string &_fragment)
{
  m_shaderProgram = glCreateProgram();
  m_name = _name;

  loadShader(_vertex, GL_VERTEX_SHADER);
  loadShader(_fragment, GL_FRAGMENT_SHADER);

  glLinkProgram(m_shaderProgram);
}

void Shader::loadShader(const std::string &_filename, const GLenum _shaderType)
{
  // creation of the vertex shader
  GLuint newShader = glCreateShader(_shaderType);
  std::string shaderFile = loadShaderFile(_filename);
  const GLchar* shaderFilePtr = static_cast<const GLchar*>(shaderFile.c_str());
  glShaderSource(newShader, 1, &shaderFilePtr, nullptr);
  glCompileShader(newShader);
  glAttachShader(m_shaderProgram, newShader);

  GLint status;
  glGetShaderiv(newShader, GL_COMPILE_STATUS, &status);
  if (!status)
  {
    GLchar buffer[500];
    glGetShaderInfoLog(newShader,
                       500,
                       nullptr,
                       buffer);
    std::string log = "shader did not compile\n";
    log += buffer;
    std::cout<<log<<'\n';
    assert(status);
  }
  glDeleteShader(newShader);
}

std::string Shader::loadShaderFile(std::string _filename)
{
  std::ifstream shaderFile(_filename);
  std::string source ((std::istreambuf_iterator<char>(shaderFile)),
                   std::istreambuf_iterator<char>());
  shaderFile.close();
  source += '\0';
  return source;
}


void Shader::setUniform(const char*_name, const float _v)
{
  auto location = glGetUniformLocation(m_shaderProgram, _name);
  glUniform1f(location, _v);
}

void Shader::setUniform(const char*_name, const float _v0, const float _v1)
{
  auto location = glGetUniformLocation(m_shaderProgram, _name);
  glUniform2f(location, _v0, _v1);
}

void Shader::setUniform(const char*_name, const float _v0, const float _v1, const float _v2)
{
  auto location = glGetUniformLocation(m_shaderProgram, _name);
  glUniform3f(location, _v0, _v1, _v2);
}

void Shader::setUniform(const char*_name, const float _v0, const float _v1, const float _v2, const float _v3)
{
  auto location = glGetUniformLocation(m_shaderProgram, _name);
  glUniform4f(location, _v0, _v1, _v2, _v3);
}

void Shader::setUniform(const char*_name, const glm::vec2 _v)
{
  auto location = glGetUniformLocation(m_shaderProgram, _name);
  glUniform2fv(location, 1, glm::value_ptr(_v));
}

void Shader::setUniform(const char*_name, const glm::vec3 _v)
{
  auto location = glGetUniformLocation(m_shaderProgram, _name);
  glUniform3fv(location, 1, glm::value_ptr(_v));
}

void Shader::setUniform(const char*_name, const glm::vec4 _v)
{
  auto location = glGetUniformLocation(m_shaderProgram, _name);
  glUniform4fv(location, 1, glm::value_ptr(_v));
}


void Shader::use()
{
  glUseProgram(m_shaderProgram);
}

std::string Shader::getName()
{
  return m_name;
}

GLuint Shader::getShaderProgram()
{
  return m_shaderProgram;
}

