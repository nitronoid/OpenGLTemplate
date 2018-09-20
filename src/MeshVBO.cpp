#include "MeshVBO.h"
#include <numeric>
#include <cassert>

using namespace glt;

//-----------------------------------------------------------------------------------------------------
void MeshVBO::init()
{
  // Generate all our required buffers
  m_vbo.create();
  m_vbo.bind();
  m_ebo.create();
  m_ebo.bind();
}
//-----------------------------------------------------------------------------------------------------
void MeshVBO::reset(const unsigned char _indicesSize, const int _nIndices, const unsigned char _dataSize, const int _nVert, const int _nUV, const int _nNorm)
{
  // Set our data type size
  m_dataSize = _dataSize;
  // Reset everything else to 0
  m_amountOfData = {0,0,0};
  m_totalAmountOfData = 0;
  m_numIndices = 0;
  m_indicesSize = 0;
  // Extend our zerod buffer
  extend(_indicesSize, _nIndices, _nVert, _nUV, _nNorm);
}
//-----------------------------------------------------------------------------------------------------
void MeshVBO::extend(const unsigned char _indicesSize, const int _nIndices, const int _nVert, const int _nUV, const int _nNorm)
{
  {
    using namespace MeshAttribute;
    // Track the amount of data being stored
    m_amountOfData[VERTEX] += _nVert;
    m_amountOfData[UV]     += _nUV;
    m_amountOfData[NORMAL] += _nNorm;
  }
  m_totalAmountOfData += _nVert + _nNorm + _nUV;
  // For all the buffers, we bind them then clear the data pointer
  m_vbo.bind();
  m_vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  m_vbo.allocate(m_dataSize * m_totalAmountOfData);

  m_numIndices += _nIndices;
  m_indicesSize += _indicesSize;
  m_ebo.bind();
  m_ebo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  m_ebo.allocate(m_numIndices * m_indicesSize);
}
//-----------------------------------------------------------------------------------------------------
void MeshVBO::write(const void *_address, const MeshAttribute::ATTRIB _section, const int _amount, const int _offset)
{
  assert(_amount <= m_amountOfData[_section]);
  // Bind the requested buffer, then set it's data pointer
  m_vbo.bind();
  m_vbo.write(offset(_section) + _offset * m_dataSize, _address, _amount * m_dataSize);
}
//-----------------------------------------------------------------------------------------------------
void MeshVBO::writeIndices(const void* _indices, const int _amount, const int _offset)
{
  assert(_amount <= m_numIndices);
  m_ebo.bind();
  m_ebo.write(_offset * m_indicesSize, _indices, _amount * m_indicesSize);
}
//-----------------------------------------------------------------------------------------------------
unsigned char MeshVBO::dataSize() const noexcept
{
  // Returns the size the stored of data elements
  return m_dataSize;
}
//-----------------------------------------------------------------------------------------------------
int MeshVBO::dataAmount() const noexcept
{
  // Returns the amount of data elements
  return m_totalAmountOfData;
}
//-----------------------------------------------------------------------------------------------------
int MeshVBO::dataAmount(const MeshAttribute::ATTRIB _section) const noexcept
{
  // Returns the amount of data elements
  return m_amountOfData[_section];
}
//-----------------------------------------------------------------------------------------------------
int MeshVBO::offset(const MeshAttribute::ATTRIB _section) const noexcept
{
  int offset = 0;
  for (size_t i = 0; i < _section; ++i)
    offset += m_amountOfData[i];
  return offset * m_dataSize;
}
//-----------------------------------------------------------------------------------------------------
void MeshVBO::use()
{
  m_vbo.bind();
  m_ebo.bind();
}
