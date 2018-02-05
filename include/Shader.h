#ifndef Shader_h
#define Shader_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <string>
#include <fstream>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
public:
  Shader() = default;
  Shader(const Shader&) = default;
  Shader& operator=(const Shader&) = default;
  Shader(Shader&&) = default;
  Shader& operator=(Shader&&) = default;
  ~Shader() = default;

  void init(const std::string &_name, const std::string &_vertex, const std::string &_fragment);
  std::string getName();
  GLuint getShaderProgram();

  //------Floats--------------------------------------------------------------------------------------------------
  void setUniform(const char*_name, const float _v);
  void setUniform(const char*_name, const float _v0, const float _v1);
  void setUniform(const char*_name, const float _v0, const float _v1, const float _v2);
  void setUniform(const char*_name, const float _v0, const float _v1, const float _v2, const float _v3);

  void setUniform(const char*_name, const glm::vec2 _v);
  void setUniform(const char*_name, const glm::vec3 _v);
  void setUniform(const char*_name, const glm::vec4 _v);

  void use();

private:
	std::string m_name;
  GLuint m_shaderProgram;
  void loadShader(const std::string &_filename, const GLenum _shaderType);
  std::string loadShaderFile(std::string _filename);

};

#endif /* Shader_h */
