#include "../../include/buffers/volatilebuffer.h"

#include "../../includes.h"

namespace core {

////////////////////////////////////////////////////////////////

VolatileBuffer::VolatileBuffer(const Buffer* pBuffer, size_t uiSize) :
pBuffer_(pBuffer), uiSize_(uiSize), uiPos_(0)
{
  ASSERT(pBuffer != NULL || uiSize_ == 0);
}

////////////////////////////////////////////////////////////////

void VolatileBuffer::readData(Buffer* pBuffer, size_t uiSize) const
{
  ASSERT(uiPos_ + uiSize <= uiSize_);

  memcpy(pBuffer, &pBuffer_[uiPos_], uiSize);
  uiPos_ += uiSize;
}

////////////////////////////////////////////////////////////////

void VolatileBuffer::setPosition(size_t uiNewPos)
{
  if (uiNewPos > uiSize_)
    uiPos_ = uiSize_;
  else
    uiPos_ = uiNewPos;
}

////////////////////////////////////////////////////////////////

}
