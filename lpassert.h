#pragma once

#include <csignal>

#ifdef DEBUG
#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#else
#define ASSERT(expr) ((void)0)
#endif

