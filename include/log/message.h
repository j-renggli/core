#ifndef COMMON_LOGGING_MESSAGE_H
#define COMMON_LOGGING_MESSAGE_H

// Local
#include "../../includes.h"

namespace core {

////////////////////////////////////////////////////////////////

class Message
{
  private:
    /// Time of message's creation
    boost::posix_time::ptime msgTime_;

    /// Priority level
    int iLevel_;

    /// Originating file
    boost::filesystem::path pathFile_;

    /// Originating line
    int iLine_;

    /// Message
    std::stringstream ssMsg_;

  public:
    /// Reset the message to accept next one
    void reset(int iLevel, const boost::filesystem::path& pathFile, int iLine)
    {
      msgTime_ = boost::posix_time::second_clock::local_time();
      iLevel_ = iLevel;
      pathFile_ = pathFile;
      iLine_ = iLine;
      ssMsg_.str("");
    }

    const boost::filesystem::path& getFile() const { return pathFile_; }

    const int getLevel() const { return iLevel_; }

    const int getLine() const { return iLine_; }

    const boost::posix_time::ptime& getTime() const { return msgTime_; }

    const std::string getMessage() const { return ssMsg_.str(); }

    template<class T> Message& operator<<(T t)
    {
      ssMsg_ << t;
      return *this;
    }
};

////////////////////////////////////////////////////////////////

}

#endif
