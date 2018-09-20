#ifndef MATERIALPBR_H
#define MATERIALPBR_H

#include "Material.h"
#include "vec3.hpp"

namespace glt
{

class MaterialPBR : public Material
{
public:
  MaterialPBR(
      std::shared_ptr<Camera> io_camera,
      std::shared_ptr<ShaderLib> io_shaderLib,
      std::array<glm::mat4, 3>* io_matrices,
      const glm::vec3 &_albedo,
      const float _ao,
      const float _exposure,
      const float _roughness,
      const float _metallic
      ) :
    Material(std::move(io_camera), std::move(io_shaderLib), io_matrices),
    m_albedo(_albedo),
    m_ao(_ao),
    m_exposure(_exposure),
    m_roughness(_roughness),
    m_metallic(_metallic)
  {}
  MaterialPBR(const MaterialPBR&) = default;
  MaterialPBR& operator=(const MaterialPBR&) = default;
  MaterialPBR(MaterialPBR&&) = default;
  MaterialPBR& operator=(MaterialPBR&&) = default;
  ~MaterialPBR() override = default;

  virtual void init() override;

  virtual void update() override;

  virtual const char* shaderFileName() const override;


private:
  glm::vec3 m_albedo;
  float m_ao;
  float m_exposure;
  float m_roughness;
  float m_metallic;

};

}

#endif // MATERIALPBR_H
