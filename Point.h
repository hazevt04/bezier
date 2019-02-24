#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include <string>


#include "Util.h"

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
      void set_x( ulong x ) {
         this->x = x;
      }
      void set_y( ulong y ) {
         this->y = y;
      }
      void set_x_y( ulong x, ulong y ) {
         this->x = x;
         this->y = y;
      }
      ulong get_x( ) { return this->x; }
      ulong get_y( ) { return this->y; }
      Point& operator=( const Point& other ) {
         if ( this != &other ) {
            this->x = other.x;
            this->y = other.y;
         }
         return *this;
      }
      bool operator==( const Point& other ) {
         if ( this != &other ) {
            return ( ( other.x == this->x ) && ( other.y == this->y ) );
         } else {
            return true;
         }
      }
      friend Point operator*( const double val, const Point& point ) {
         Point product;
         product.x = point.x * val;
         product.y = point.y * val;
         return product;
      }
      friend Point operator*( const Point& point, const double val ) {
         Point product;
         product.x = point.x * val;
         product.y = point.y * val;
         return product;
      }
      friend Point operator*( const int val, const Point& point ) {
         Point product;
         product.x = point.x * val;
         product.y = point.y * val;
         return product;
      }
      friend Point operator*( const Point& point, const int val ) {
         Point product;
         product.x = point.x * val;
         product.y = point.y * val;
         return product;
      }
      friend Point operator+( const double val, const Point& point ) {
         Point sum;
         sum.x = point.x + val;
         sum.y = point.y + val;
         return sum;
      }
      friend Point operator+( const Point& point, const double val ) {
         Point sum;
         sum.x = point.x + val;
         sum.y = point.y + val;
         return sum;
      }
      friend Point operator+( const int val, const Point& point ) {
         Point sum;
         sum.x = point.x + val;
         sum.y = point.y + val;
         return sum;
      }
      friend Point operator+( const Point& point, const int val ) {
         Point sum;
         sum.x = point.x + val;
         sum.y = point.y + val;
         return sum;
      }
      friend Point operator+( const Point& point1, const Point& point2 ) {
         Point sum;
         sum.x = point1.x + point2.x;
         sum.y = point1.y + point2.y;
         return sum;
      }
      friend std::ostream& operator<<( std::ostream& os, const Point& point ) {
         os << "(" << point.x << ", " << point.y << ")";
         return os;
      }
      void display( ) {
         std::cout << "(" << x << ", " << y << ")";
      }
   private:
      ulong x;
      ulong y;
};

#endif
