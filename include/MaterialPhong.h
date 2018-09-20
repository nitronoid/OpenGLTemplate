#ifndef MATERIALPHONG_H
#define MATERIALPHONG_H

#include "Material.h"

namespace glt
{

class MaterialPhong : public Material
{
public:
  MaterialPhong(std::shared_ptr<Camera> io_camera, std::shared_ptr<ShaderLib> io_shaderLib, std::array<glm::mat4, 3>* io_matrices) 
    : Material(std::move(io_camera), std::move(io_shaderLib), io_matrices)
  {}
  MaterialPhong(const MaterialPhong&) = default;
  MaterialPhong& operator=(const MaterialPhong&) = default;
  MaterialPhong(MaterialPhong&&) = default;
  MaterialPhong& operator=(MaterialPhong&&) = default;
  ~MaterialPhong() override = default;

  virtual void init() override;

  virtual void update() override;

  virtual const char* shaderFileName() const override;

};

}

#endif // MATERIALPHONG_H
