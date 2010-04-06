#ifndef CORE_INCLUDE_BUFFERS_FILE_H
#define CORE_INCLUDE_BUFFERS_FILE_H

#include "membuffer.h"
#include "../iobuffer.h"
#include "../resultcode.h"

namespace core {

class FileReadBuffer : virtual public IReadBuffer
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

    /// The current size of the buffer
    mutable size_t uiSize_;

    /// The current position
    mutable size_t uiPos_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    FileReadBuffer();
    virtual ~FileReadBuffer();

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:
    // Assignment
    FileReadBuffer& operator=(const FileReadBuffer& buffer) { return *this; }

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    /// Is the buffer empty ?
    virtual bool isEmpty() const { return uiSize_ == 0; }

    /// Get the raw buffer
    virtual const Buffer* getBuffer() const { return pBuffer_; }

    /// Get the position of the buffer's cursor
    virtual size_t getPosition() const { return uiPos_; }

    /// Read N characters
    virtual void readData(Buffer* pBuffer, size_t uiSize) const;

    /// Restore a buffer from a file
    ResultCode restore(const boost::filesystem::path& pathFile);

    /// Set the position of the buffer's cursor
    /// @param uiNewPos the position; uiSize if uiNewPos >= uiSize
    void setPosition(size_t uiNewPos);

    /// Get the current size of the buffer
    virtual size_t getSize() const { return uiSize_; }
};

////////////////////////////////////////////////////////////////

class FileWriteBuffer : virtual public MemBuffer
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    FileWriteBuffer();
    virtual ~FileWriteBuffer() {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:
    // Assignment: disabled
    FileWriteBuffer& operator=(const FileWriteBuffer& buffer) { return *this; }

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    /// Serialise the buffer to the file on disk
    ResultCode serialise(const boost::filesystem::path& pathFile);
};

}

#endif
