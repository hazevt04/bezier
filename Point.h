#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include <sstream>
#include <string>

#include "util.h"

class Point {
   public:
      Point( ) { }
      Point( const Point& other_point ) { 
         this->x = other_point.x;
         this->y = other_point.y;
      }
      ~Point( ) { }
      Point( ulong  x, ulong y ) { 
         this->x = x;
         this->y = y;

      }
      void set_x_y( ulong x, ulong y ) {
         this->x = x;
         this->y = y;
      }
      ulong get_x( ) { return this->x; }
      ulong get_y( ) { return this->y; }
      void operator = ( const Point& other ) {
         x = other.x;
         y = other.y;
      }
      void display( ) {
         std::cout << "(" << x << ", " << y << ")";
      }
   private:
      ulong x;
      ulong y;
};

#endif
