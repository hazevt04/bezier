#ifndef _LINE_H_
#define _LINE_H_

#include <iostream>
#include <utility>
#include <string>

#include "ImageData.h"
#include "Point.h"

using std::string;
using std::ostream;
using std::cout;
using std::endl;

class Line {
   public:
      Line( ) { }
      Line( const Line& other_line ) { 
         this->start_point = other_line.start_point;
         this->end_point = other_line.end_point;
         this->color = other_line.color;
      }
      Line( Point* start_point, Point* end_point, 
            ulong color=Util::BLACK ) {
         this->start_point = *start_point;
         this->end_point = *end_point;
         this->color = color;
      }
      ~Line() { }
      Point get_start_point( ) { return this->start_point; }      
      Point get_end_point( ) { return this->end_point; }
      ulong get_color( ) { return this->color; }
      void  set_start_point( Point start_point ) {
         this->start_point = start_point;
      }      
      void  set_end_point( Point end_point ) {
         this->end_point = end_point;
      }
      void  set_color( ulong color ) { this->color = color; }
      friend ostream& operator<<( ostream& os, const Line& line ) {
         os << "Line is from " << line.start_point << " to " 
            << line.end_point << endl;
         return os;
      }
      void display( ) {
         std::cout << "Line is from ";
         this->start_point.display();
         std::cout << " to ";
         this->end_point.display();
         std::cout << std::endl;
      }
   private:
      Point start_point;    
      Point end_point;    
      ulong color;
};


#endif
