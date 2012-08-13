#include "include/log/coutdisplay.h"

#include <iostream>

namespace core {

void COutDisplay::display(const Message& msg)
{
  if (msg.getLevel() < iMinLevel_)
    return;

  // \x1b[0m -> Reset attributes
  // \x1b[22m -> Normal intensity
  // \x1b[31m -> RED FG
  // \x1b[35m -> MAGENTA FG
  if (msg.getLevel() >= LogManager::eError)
    std::cout << "\x1b[31m\x1b[22m" << msg.getMessage() << " (" << msg.getFile().leaf() << "@" << msg.getLine() << ")\x1b[0m" << std::endl;
  else if (msg.getLevel() >= LogManager::eWarning)
    std::cout << "\x1b[35m\x1b[22m" << msg.getMessage() << " (" << msg.getFile().leaf() << "@" << msg.getLine() << ")\x1b[0m" << std::endl;
  else
    std::cout << msg.getMessage() << " (" << msg.getFile().leaf() << "@" << msg.getLine() << ")" << std::endl;
//  std::cout << msg.getFile().leaf() << " @ " << msg.getLine() << " (" << msg.getLevel() << "): "
//    << msg.getMessage() << std::endl;
}

}
