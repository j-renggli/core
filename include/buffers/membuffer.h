#ifndef CORE_INCLUDE_BUFFERS_MEMORY_H
#define CORE_INCLUDE_BUFFERS_MEMORY_H

#include "../iobuffer.h"

namespace core {

class MemBuffer : virtual public IReadWriteBuffer
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:
    typedef uint8_t Buffer;

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    /// The buffer
    Buffer* pBuffer_;

    /// The maximum size of the buffer
    size_t uiMaxSize_;

    /// The current size of the buffer
    mutable size_t uiSize_;

    /// The current position
    mutable size_t uiPos_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    MemBuffer();
    virtual ~MemBuffer();

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  public:
    // Assignment
    MemBuffer& operator=(const MemBuffer& buffer);

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    /// Clear the buffer
    void clear() { uiSize_ = 0; uiPos_ = 0; }

    /// Is the buffer empty ?
    virtual bool isEmpty() const { return uiSize_ == 0; }

    /// Direct access to buffer
    Buffer* getBuffer() { return pBuffer_; }
    const Buffer* getBuffer() const { return pBuffer_; }

    /// Get the position of the buffer's cursor
    virtual size_t getPosition() const { return uiPos_; }

    /// Read N characters
    virtual void readData(Buffer* pBuffer, size_t uiSize) const;

    /// Resize the buffer : max size might be larger to avoid too many reallocations
    void resize(size_t uiNewSize);

    /// Set the position of the buffer's cursor
    /// @param uiNewPos the position; uiSize if uiNewPos >= uiSize
    void setPosition(size_t uiNewPos);

    /// Get the current size of the buffer
    virtual size_t getSize() const { return uiSize_; }

    /// Write N characters
    virtual void writeData(const Buffer* pBuffer, size_t uiSize);
};

}

#endif
