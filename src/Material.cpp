#include "Material.h"

using namespace glt;

//-----------------------------------------------------------------------------------------------------
Material::~Material() = default;
//-----------------------------------------------------------------------------------------------------
void Material::apply()
{
  m_shaderLib->useShader(m_shaderName);
  init();
}
//-----------------------------------------------------------------------------------------------------
void Material::setShaderName(const std::string &_name)
{
  m_shaderName = _name;
}
//-----------------------------------------------------------------------------------------------------
void Material::handleKey(QKeyEvent*, QOpenGLContext*)
{}
