#include "../../includes.h"

namespace core {

////////////////////////////////////////////////////////////////

FileReadBuffer::FileReadBuffer() :
pBuffer_(NULL),
uiSize_(0),
uiPos_(0)
{
}

////////////////////////////////////////////////////////////////

FileReadBuffer::~FileReadBuffer()
{
  if (pBuffer_ != NULL)
    delete[] pBuffer_;
}

////////////////////////////////////////////////////////////////

void FileReadBuffer::readData(Buffer* pBuffer, size_t uiSize) const
{
  assert(uiPos_ + uiSize <= uiSize_);

  memcpy(pBuffer, &pBuffer_[uiPos_], uiSize);
  uiPos_ += uiSize;
}

////////////////////////////////////////////////////////////////

ResultCode FileReadBuffer::restore(const boost::filesystem::path& pathFile)
{
  if (!exists(pathFile) || !is_regular(pathFile))
  {
    return rcFailure;
  }

  std::ifstream fileIn(pathFile.native_file_string().c_str(), std::ios::binary);
  if (!fileIn)
  {
    return rcFailure;
  }

  uiPos_ = 0;
  uiSize_ = 4096;
  char pTemp[4096];
  while (true)
  {
    fileIn.read(pTemp, uiSize_);
    if (fileIn.bad())
    {
      return rcFailure;
    }

    size_t uiCount = fileIn.gcount();
    if (uiCount == 0)
      break;
    Buffer* pNewBuffer = new Buffer[uiPos_ + uiCount];
    memcpy(pNewBuffer, pBuffer_, uiPos_);
    memcpy(pNewBuffer+uiPos_, pTemp, uiCount);
    delete[] pBuffer_;
    pBuffer_ = pNewBuffer;
    uiPos_ += uiCount;

    if (uiCount < uiSize_)
      break;
  }

  uiSize_ = uiPos_;
  uiPos_ = 0;

  fileIn.close();

  return rcSuccess;
}

////////////////////////////////////////////////////////////////

void FileReadBuffer::setPosition(size_t uiNewPos)
{
  if (uiNewPos > uiSize_)
    uiPos_ = uiSize_;
  else
    uiPos_ = uiNewPos;
}

////////////////////////////////////////////////////////////////

FileWriteBuffer::FileWriteBuffer() :
MemBuffer()
{
}

////////////////////////////////////////////////////////////////

ResultCode FileWriteBuffer::serialise(const boost::filesystem::path& pathFile)
{
  std::ofstream fileOut(pathFile.native_file_string().c_str(), std::ios::binary);
  if (!fileOut)
  {
    return rcFailure;
  }

  fileOut.write((const char*)getBuffer(), getSize());

  fileOut.close();

  return rcSuccess;
}

////////////////////////////////////////////////////////////////

}
