#pragma once

#include <vector>
#include <sys/types.h>

#include <unicode/unistr.h>

namespace core {

typedef uint8_t Buffer;

class IReadBuffer
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    virtual ~IReadBuffer() {}

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    /// Is the buffer empty ?
    /// Return true if size() == 0
    virtual bool isEmpty() const = 0;

    /// Direct access to buffer... should NEVER be modified through this function as it is a read buffer
    virtual const Buffer* getBuffer() const = 0;

    /// Read N characters
    virtual void readData(Buffer* pBuffer, const size_t uiSize) = 0;

    /// Useful functions to read most common objects; can be extended !
    /// @param value the value is read, as big endian if applicable, into that parameter
    template <class T>
    void readValue(T& value);

    /// Endianness-specific functions
    template <class T>
    void readValue(T& value, bool isBigEndian)
    {
      // TODO: mixed-endian too ?
      readValue(value);
      if (!isBigEndian)
      {
        int len = sizeof(T);
        // TODO: ASSERT(len % 2 == 0);

        Buffer* pData = (Buffer*)(&value);
        Buffer temp;
        for (int i = 0; i < len / 2; ++i)
        {
          temp = pData[i];
          pData[i] = pData[len - i - 1];
          pData[len - i - 1] = temp;
        }
      }
    }

    template <class T>
    T read()
    {
      T value;
      readValue(value);
      return value;
    }

    template <class T>
    T read(bool isBigEndian)
    {
      T value;
      readValue(value, isBigEndian);
      return value;
    }

    /// Read the most common objects in vector form
    template <class T>
    void readValue(std::vector<T>& vValues)
    {
      const size_t size = read<u_int32_t>();
      vValues.resize(size);

      for (size_t i = 0; i < size; ++i)
      {
        readValue(vValues[i]);
      }
    }

    /// Get the position of the buffer's cursor
    virtual size_t getPosition() const = 0;

    /// Get the current size of the buffer
    virtual size_t getSize() const = 0;

    /// Set the position of the buffer's cursor
    /// @param uiNewPos the position; uiSize if uiNewPos >= uiSize
    virtual void setPosition(size_t uiNewPos) = 0;
};

////////////////////////////////////////////////////////////////

class IWriteBuffer
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    virtual ~IWriteBuffer() {}

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////

  public:
    /// Clear the buffer
    virtual void clear() = 0;

    /// Direct access to buffer...
    virtual Buffer* getBuffer() = 0;

    /// Get the position of the buffer's cursor
    virtual size_t getPosition() const = 0;

    /// Get the current size of the buffer
    virtual size_t getSize() const = 0;

    /// Reserve enough space for the buffer without resizing it
    virtual void reserve(size_t newSize) = 0;

    /// Resize the buffer
    virtual void resize(size_t newSize) = 0;

    /// Set the position of the buffer's cursor
    /// @param uiNewPos the position; uiSize if uiNewPos >= uiSize
    virtual void setPosition(size_t uiNewPos) = 0;

    /// Append data to the buffer
    virtual void writeData(const Buffer* pBuffer, const size_t uiSize) = 0;

    /// Write most common objects; can be extended !
    template <class T>
    void write(const T& value);

    /// Write the most common objects in vector form
    template <class T>
    void write(const std::vector<T>& vValues)
    {
      write<u_int32_t>(vValues.size());

      for (size_t i = 0; i < vValues.size(); ++i)
      {
        write(vValues[i]);
      }
    }
};

////////////////////////////////////////////////////////////////

class IReadWriteBuffer : virtual public IReadBuffer, virtual public IWriteBuffer
{
  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    virtual ~IReadWriteBuffer() {}

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    virtual Buffer* getBuffer() = 0;

    virtual const Buffer* getBuffer() const = 0;

    virtual size_t getPosition() const = 0;

    virtual size_t getSize() const = 0;

    virtual void setPosition(size_t uiNewPos) = 0;
};

}
