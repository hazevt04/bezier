#ifndef _BEZIERCURVE_H_
#define _BEZIERCURVE_H_

// Header File for BezierCurve Class

#include "Point.h"
#include "Line.h"

class BezierCurve {
   public:
      BezierCurve( ); 
      ~BezierCurve( ); 
      
      BezierCurve( int order, Point* control_points, int num_curve_points );
      void generateCurve( );

      Line* getLines( ) { return this->lines; }
      int get_num_curve_points( ) { return this->num_curve_points; }
      int get_num_lines( ) { return this->num_lines; }
   private:
      int binomial( int n_val, int k_val );
      double n_order_calc( int num, double t_val, int weights[] );
      double second_order_calc( double t_val, int weights[] );
      double third_order_calc( double t_val, int weights[] );
      
      Point third_order_calc( double t_val );
      
      int order;
      int num_curve_points;
      int num_lines;
      Point* control_points;
      Line* lines;
};




// end of header file for BezierCurve Class
#endif
