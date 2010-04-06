#ifndef CORE_INCLUDE_BUFFERS_VOLATILE_H
#define CORE_INCLUDE_BUFFERS_VOLATILE_H

#include "../../includes.h"

namespace core {

class VolatileBuffer : virtual public IReadBuffer
{
  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    /// The volatile buffer
    const Buffer* pBuffer_;

    /// The size of the buffer
    const size_t uiSize_;

    /// The current position
    mutable size_t uiPos_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    VolatileBuffer(const Buffer* pBuffer, size_t uiSize);

    virtual ~VolatileBuffer() {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    /// Is the buffer empty ?
    /// Return true if size() == 0
    virtual bool isEmpty() const { return uiSize_ == 0; }

    /// Direct access to buffer
    virtual const Buffer* getBuffer() const { return pBuffer_; }

    /// Read N characters
    virtual void readData(Buffer* pBuffer, size_t uiSize) const;

    /// Get the current size of the buffer
    virtual size_t getSize() const { return uiSize_; }
};

}

#endif
