#ifndef MATERIALWIREFRAME_H
#define MATERIALWIREFRAME_H

#include "Material.h"

namespace glt
{

class MaterialWireframe : public Material
{
public:
  MaterialWireframe(std::shared_ptr<Camera> io_camera, std::shared_ptr<ShaderLib> io_shaderLib, std::array<glm::mat4, 3>* io_matrices)
    : Material(std::move(io_camera), std::move(io_shaderLib), io_matrices)
  {}
  MaterialWireframe(const MaterialWireframe&) = default;
  MaterialWireframe& operator=(const MaterialWireframe&) = default;
  MaterialWireframe(MaterialWireframe&&) = default;
  MaterialWireframe& operator=(MaterialWireframe&&) = default;
  ~MaterialWireframe() override = default;

  virtual void init() override;

  virtual void update() override;

  virtual const char* shaderFileName() const override;

};

}

#endif // MATERIALWIREFRAME_H
