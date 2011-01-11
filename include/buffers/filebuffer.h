#pragma once

#include "membuffer.h"
#include "../iobuffer.h"
#include "../resultcode.h"

#include <boost/filesystem.hpp>

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
    size_t uiSize_;

    /// The current position
    size_t uiPos_;

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
    virtual void readData(Buffer* pBuffer, size_t uiSize);

    /// Restore a buffer from a file
    ResultCode restore(const boost::filesystem::path& pathFile);

    /// Set the position of the buffer's cursor
    /// @param uiNewPos the position; uiSize if uiNewPos >= uiSize
    void setPosition(size_t uiNewPos);

    /// Get the current size of the buffer
    virtual size_t getSize() const { return uiSize_; }
};

////////////////////////////////////////////////////////////////

class FileReadWriteBuffer : virtual public MemBuffer
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    boost::filesystem::path pathFile_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    FileReadWriteBuffer(const boost::filesystem::path& filePath = "");
    virtual ~FileReadWriteBuffer() {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:
    // Assignment: disabled
    FileReadWriteBuffer& operator=(const FileReadWriteBuffer& buffer) { return *this; }

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    /// Change the path
    ResultCode changePath(const boost::filesystem::path& filePath);

    /// Restore a buffer from a file
    ResultCode restore();

    /// Serialise the buffer to the file on disk
    ResultCode serialise();
};

////////////////////////////////////////////////////////////////

}
