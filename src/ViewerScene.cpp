#include "ViewerScene.h"
#include "MaterialWireframe.h"
#include "MaterialPBR.h"
#include "MaterialPhong.h"
#include <QOpenGLContext>

using namespace glt;

//-----------------------------------------------------------------------------------------------------
void ViewerScene::writeMeshAttributes()
{
  auto&& mesh = m_meshes[m_meshIndex];

  using namespace MeshAttribute;
  for (const auto buff : {VERTEX, UV, NORMAL})
  {
    m_meshVBO.write(mesh.getAttribData(buff), buff, mesh.getNAttribData(buff));
  }
  m_meshVBO.writeIndices(mesh.getIndicesData(), mesh.getNIndicesData());
}
//-----------------------------------------------------------------------------------------------------
void ViewerScene::setAttributeBuffers()
{
  static constexpr int tupleSize[] = {3,2,3};
  auto prog = m_shaderLib->getCurrentShader();

  using namespace MeshAttribute;
  for (const auto buff : {VERTEX, UV, NORMAL})
  {
    prog->enableAttributeArray(buff);
    prog->setAttributeBuffer(buff, GL_FLOAT, m_meshVBO.offset(buff), tupleSize[buff]);
  }

}
//-----------------------------------------------------------------------------------------------------
void ViewerScene::init()
{
  Scene::init();

  initMaterials();

  initGeo();

  // Scope the using declaration
  {
    using namespace SceneMatrices;
    m_matrices[MODEL_VIEW] = glm::translate(m_matrices[MODEL_VIEW], glm::vec3(0.0f, 0.0f, -2.0f));
  }
}
//-----------------------------------------------------------------------------------------------------
void ViewerScene::initGeo()
{
  m_meshes[0].load("models/cube.obj");
  m_meshes[1].load("models/plane.obj");
  m_meshes[2].load("models/Face.obj");
  m_meshes[3].load("models/Suzanne.obj");
  m_meshes[4].load("models/test2.obj");
  m_meshes[5].load("models/Asteroid.obj");
  // Create and bind our Vertex Array Object
  m_vao->create();
  m_vao->bind();
  // Create and bind our Vertex Buffer Object
  m_meshVBO.init();
  generateNewGeometry();
}
//-----------------------------------------------------------------------------------------------------
void ViewerScene::keyPress(QKeyEvent* io_event)
{
  makeCurrent();
  Scene::keyPress(io_event);
  m_materials[m_currentMaterial]->handleKey(io_event, context());
}
//-----------------------------------------------------------------------------------------------------
void ViewerScene::initMaterials()
{
  m_materials.reserve(7);

  m_materials.emplace_back(new MaterialPhong(m_camera, m_shaderLib, &m_matrices));
  m_materials.emplace_back(new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {0.5f, 0.0f, 0.0f}, 1.0f, 1.0f, 0.5f, 1.0f));
  m_materials.emplace_back(new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {0.1f, 0.2f, 0.5f}, 0.5f, 1.0f, 0.4f, 0.2f));
  m_materials.emplace_back(new MaterialWireframe(m_camera, m_shaderLib, &m_matrices));


  for (auto&& mat : m_materials)
  {
    auto name = m_shaderLib->loadShaderProg(mat->shaderFileName());
    mat->setShaderName(name);
    mat->apply();
  }

  m_materials[m_currentMaterial]->apply();
}
//-----------------------------------------------------------------------------------------------------
void ViewerScene::rotating( const bool _rotating )
{
  m_rotating = _rotating;
}
//-----------------------------------------------------------------------------------------------------
void ViewerScene::generateNewGeometry()
{
  makeCurrent();
  m_meshIndex = (m_meshIndex + 1) % m_meshes.size();
  auto&& mesh = m_meshes[m_meshIndex];
  m_meshVBO.reset(
        sizeof(GLushort),
        mesh.getNIndicesData(),
        sizeof(GLfloat),
        mesh.getNVertData(),
        mesh.getNUVData(),
        mesh.getNNormData()
        );
  writeMeshAttributes();
  setAttributeBuffers();
}
//-----------------------------------------------------------------------------------------------------
void ViewerScene::nextMaterial()
{
  makeCurrent();
  m_currentMaterial = (m_currentMaterial + 1) % m_materials.size();

  m_materials[m_currentMaterial]->apply();
  setAttributeBuffers();
}
//-----------------------------------------------------------------------------------------------------
void ViewerScene::renderScene()
{
  Scene::renderScene();

  // Scope the using declaration
  {
    using namespace SceneMatrices;
    m_matrices[MODEL_VIEW] = glm::rotate(m_matrices[MODEL_VIEW], glm::radians(-1.0f * m_rotating), glm::vec3(0.0f, 1.0f, 0.0f));
  }

  m_materials[m_currentMaterial]->update();

  m_meshVBO.use();
  glDrawElements(GL_TRIANGLES, m_meshes[m_meshIndex].getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
//  glDrawArrays(GL_TRIANGLES, 0, m_meshes[m_meshIndex].getNVertData()/3);
}
//-----------------------------------------------------------------------------------------------------
