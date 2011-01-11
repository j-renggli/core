#include "../include/iobuffer.h"

#include "../include/string.h"

namespace core {

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(bool& value)
{
  int8_t val = read<int8_t>();
  value = val != 0;
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(u_int8_t& value)
{
  readData(&value, 1);
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(int8_t& value)
{
  readData((u_int8_t*)(&value), 1);
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(u_int16_t& value)
{
  value = 0;
  Buffer buffer[2];
  readData(buffer, 2);
  for (int i = 0; i < 2; ++i)
  {
    value <<= 8;
    value |= buffer[i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(int16_t& value)
{
  value = 0;
  Buffer buffer[2];
  readData(buffer, 2);
  for (int i = 0; i < 2; ++i)
  {
    value <<= 8;
    value |= buffer[i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(u_int32_t& value)
{
  value = 0;
  Buffer buffer[4];
  readData(buffer, 4);
  for (int i = 0; i < 4; ++i)
  {
    value <<= 8;
    value |= buffer[i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(int32_t& value)
{
  value = 0;
  Buffer buffer[4];
  readData(buffer, 4);
  for (int i = 0; i < 4; ++i)
  {
    value <<= 8;
    value |= buffer[i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(u_int64_t& value)
{
  value = 0;
  Buffer buffer[8];
  readData(buffer, 8);
  for (int i = 0; i < 8; ++i)
  {
    value <<= 8;
    value |= buffer[i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(int64_t& value)
{
  value = 0;
  Buffer buffer[8];
  readData(buffer, 8);
  for (int i = 0; i < 8; ++i)
  {
    value <<= 8;
    value |= buffer[i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(float& value)
{
  readData((Buffer*)(&value), sizeof(float));
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(double& value)
{
  readData((Buffer*)(&value), sizeof(double));
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(UnicodeString& value)
{
  uint32_t uiLen = read<uint32_t>();
  Buffer* pszBuffer = new Buffer[uiLen];
  readData(pszBuffer, uiLen);
  value = core::String::uncompressFromBuffer(pszBuffer, uiLen);
  delete[] pszBuffer;
}

////////////////////////////////////////////////////////////////
// Write
////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const u_int8_t& value)
{
  writeData(&value, 1);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const int8_t& value)
{
  writeData((u_int8_t*)&value, 1);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const u_int16_t& value)
{
  u_int16_t val = value;

  Buffer buffer[2];
  for (int i = 0; i < 2; ++i)
  {
    buffer[1-i] = val & 0xFF;
    val >>= 8;
  }

  writeData(buffer, 2);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const int16_t& value)
{
  int16_t val = value;

  Buffer buffer[2];
  for (int i = 0; i < 2; ++i)
  {
    buffer[1-i] = val & 0xFF;
    val >>= 8;
  }

  writeData(buffer, 2);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const u_int32_t& value)
{
  u_int32_t val = value;

  Buffer buffer[4];
  for (int i = 0; i < 4; ++i)
  {
    buffer[3-i] = val & 0xFF;
    val >>= 8;
  }

  writeData(buffer, 4);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const int32_t& value)
{
  int32_t val = value;

  Buffer buffer[4];
  for (int i = 0; i < 4; ++i)
  {
    buffer[3-i] = val & 0xFF;
    val >>= 8;
  }

  writeData(buffer, 4);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const u_int64_t& value)
{
  u_int64_t val = value;

  Buffer buffer[8];
  for (int i = 0; i < 8; ++i)
  {
    buffer[7-i] = val & 0xFF;
    val >>= 8;
  }

  writeData(buffer, 8);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const int64_t& value)
{
  int64_t val = value;

  Buffer buffer[8];
  for (int i = 0; i < 8; ++i)
  {
    buffer[7-i] = val & 0xFF;
    val >>= 8;
  }

  writeData(buffer, 8);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const bool& value)
{
  write<int8_t>(value ? 1 : 0);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const float& value)
{
  writeData((Buffer*)(&value), sizeof(float));
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const double& value)
{
  writeData((Buffer*)(&value), sizeof(double));
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const UnicodeString& value)
{
  uint32_t uiLen;
  const core::Buffer* pszText = core::String::compressToBuffer(value, uiLen);
  write(uiLen);
  writeData(pszText, uiLen);
  core::String::deleteBuffer(pszText);
}

////////////////////////////////////////////////////////////////

}
