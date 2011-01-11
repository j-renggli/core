#include "../../include/buffers/membuffer.h"

#include "../../includes.h"

namespace core {

////////////////////////////////////////////////////////////////

MemBuffer::MemBuffer() :
pBuffer_(NULL),
uiMaxSize_(0),
uiSize_(0),
uiPos_(0)
{
}

////////////////////////////////////////////////////////////////

MemBuffer::MemBuffer(const IReadBuffer& buffer):
pBuffer_(NULL),
uiMaxSize_(0),
uiSize_(0),
uiPos_(0)
{
  *this = buffer;
}

////////////////////////////////////////////////////////////////

MemBuffer::MemBuffer(const MemBuffer& buffer):
pBuffer_(NULL),
uiMaxSize_(0),
uiSize_(0),
uiPos_(0)
{
  *this = buffer;
}

////////////////////////////////////////////////////////////////

MemBuffer::~MemBuffer()
{
  if (pBuffer_!= NULL)
    delete[] pBuffer_;
}

////////////////////////////////////////////////////////////////

MemBuffer& MemBuffer::operator=(const IReadBuffer& buffer)
{
  if (&buffer == this)
    return *this;

  delete pBuffer_;
  pBuffer_ = new Buffer[buffer.getSize()];
  memcpy(pBuffer_, buffer.getBuffer(), buffer.getSize());
  uiMaxSize_ = buffer.getSize();
  uiSize_ = uiMaxSize_;
  uiPos_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////

MemBuffer& MemBuffer::operator=(const MemBuffer& buffer)
{
  if (&buffer == this)
    return *this;

  delete pBuffer_;
  pBuffer_ = new Buffer[buffer.getSize()];
  memcpy(pBuffer_, buffer.getBuffer(), buffer.getSize());
  uiMaxSize_ = buffer.getSize();
  uiSize_ = uiMaxSize_;
  uiPos_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////

void MemBuffer::readData(Buffer* pBuffer, size_t uiSize)
{
  ASSERT(uiPos_ + uiSize <= uiSize_);

  memcpy(pBuffer, &pBuffer_[uiPos_], uiSize);
  uiPos_ += uiSize;
}

////////////////////////////////////////////////////////////////

void MemBuffer::resize(size_t uiNewSize)
{
  if (uiNewSize > uiMaxSize_)
  {
    // Reallocate
    uiMaxSize_ = uiNewSize * 6 / 5; // Slightly larger
    Buffer* pNewBuffer = new Buffer[uiMaxSize_];
    memcpy(pNewBuffer, pBuffer_, uiSize_);
    delete[] pBuffer_;
    pBuffer_ = pNewBuffer;
  }

  uiSize_ = uiNewSize;
}

////////////////////////////////////////////////////////////////

void MemBuffer::setPosition(size_t uiNewPos)
{
  if (uiNewPos > uiSize_)
    uiPos_ = uiSize_;
  else
    uiPos_ = uiNewPos;
}

////////////////////////////////////////////////////////////////

void MemBuffer::writeData(const Buffer* pBuffer, size_t uiSize)
{
  resize(uiPos_ + uiSize);
  memcpy(&pBuffer_[uiPos_], pBuffer, uiSize);
  uiPos_ += uiSize;
}

////////////////////////////////////////////////////////////////

}
