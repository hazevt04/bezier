#ifndef _UTIL_H_
#define _UTIL_H_

#ifdef DEBUG
#  define DEBUG_PRINTF(args...) printf( args );
#  define DEBUG_FUNC_CALL( func ) func;
#else
   // Don't print anything
#  define DEBUG_PRINTF(args...) 
#  define DEBUG_FUNC_CALL( func )
#endif


#endif
