#include "../../include/buffers/volatilebuffer.h"

#include "../../includes.h"

namespace core {

////////////////////////////////////////////////////////////////

VolatileBuffer::VolatileBuffer(const Buffer* pBuffer, size_t uiSize) :
pBuffer_(pBuffer), uiSize_(uiSize), uiPos_(0)
{
  assert(pBuffer != NULL || uiSize_ == 0);
}

////////////////////////////////////////////////////////////////

void VolatileBuffer::readData(Buffer* pBuffer, size_t uiSize) const
{
  assert(uiPos_ + uiSize <= uiSize_);

  memcpy(pBuffer, &pBuffer_[uiPos_], uiSize);
  uiPos_ += uiSize;
}

////////////////////////////////////////////////////////////////

}
