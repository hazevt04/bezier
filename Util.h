#ifndef _UTIL_H_
#define _UTIL_H_

#ifdef DEBUG
#  define DEBUG_PRINTF(args...) printf( args );
#  define DEBUG_FUNC( func ) func;
#else
   // Don't print anything
#  define DEBUG_PRINTF(args...) 
#  define DEBUG_FUNC( func )
#endif

#include <vector>

typedef unsigned long ulong;

typedef std::vector<std::vector<int>> VoV;

namespace Util {
   static const ulong WHITE   = 0xffffffL;
   static const ulong BLACK   = 0x000000L;
   static const ulong RED     = 0xff0000L;
   static const ulong YELLOW  = 0xffff00L;
   static const ulong BLUE    = 0x0080ffL;
   static const ulong GREEN   = 0x00ff00L;
   static const ulong ORANGE  = 0xff8000L;
   static const ulong PURPLE  = 0x7f00ffL;
   static const ulong BROWN   = 0x663300L;
   static const ulong GRAY    = 0x808080L;
   static const ulong PINK    = 0xffccccL;
}

#endif
