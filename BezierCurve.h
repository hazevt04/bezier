#ifndef _BEZIERCURVE_H_
#define _BEZIERCURVE_H_

// Header File for BezierCurve Class

#include "Point.h"
#include "Line.h"

class BezierCurve {
   public:
      BezierCurve( ); 
      ~BezierCurve( ); 
      
      BezierCurve( int order, Point* control_points, int num_curve_points, 
            ulong color );
      void generate_curve( );

      Line* get_lines( ) { return this->lines; }
      int get_num_curve_points( ) { return this->num_curve_points; }
      int get_num_lines( ) { return this->num_lines; }
      
      Point calc( double t_val );
   private:
      Point second_order_calc( double t_val );
      Point third_order_calc( double t_val );
      Point n_order_calc( double t_val );
      
      int binomial( int n_val, int k_val );
      
      Line* lines;
      Point* control_points;
      ulong color;
      int order;
      int num_curve_points;
      int num_lines;
};




// end of header file for BezierCurve Class
#endif
