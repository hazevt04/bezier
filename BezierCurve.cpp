// Implementation of BezierCurve Class

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "Util.h"
#include "BezierCurve.h"

using std::vector;
using std::cout;
using std::endl;

BezierCurve::BezierCurve( ) {
   control_points = nullptr;
   lines = nullptr;
}

BezierCurve::~BezierCurve( ) {
   if ( lines ) {
      delete lines;
   }
   if ( control_points ) {
      delete control_points;
   }
}

BezierCurve::BezierCurve( int order, Point* control_points, 
      int num_curve_points = 200, ulong color = Util::BLACK ) {
   
   this->order = order;
   this->color = color;
   
   this->control_points = control_points;
   this->num_curve_points = num_curve_points + 1;
   this->num_lines = num_curve_points;

   DEBUG_PRINTF( "%s(): num_lines is %d\n", __func__, this->num_lines );
   this->lines = new Line[num_lines];
   for ( int line_num = 0; line_num < num_lines; line_num++ ) {
      this->lines[line_num].set_color( color );
   }
}

void BezierCurve::set_properties( int order, Point* control_points, 
      int num_curve_points = 200, ulong color = Util::BLACK ) {
   
   this->order = order;
   this->color = color;
   
   this->control_points = control_points;
   this->num_curve_points = num_curve_points + 1;
   this->num_lines = num_curve_points;
   
   DEBUG_PRINTF( "%s(): num_lines is %d\n", __func__, this->num_lines );
   this->lines = new Line[num_lines];
   for ( int line_num = 0; line_num < num_lines; line_num++ ) {
      this->lines[line_num].set_color( color );
   }
}

// Third order curve
void BezierCurve::generate_curve( ) {
   int num_curve_points = this->num_curve_points;
   double increment = 1.0/(double)num_curve_points;
   
   DEBUG_PRINTF( "%s(): t_index increment is %12.3f\n", __func__, increment );
   DEBUG_PRINTF( "%s(): t_index will iterate from 0.0 to 1.000.\n", __func__ );
   DEBUG_PRINTF( "%s(): There will be %f points.\n", 
         __func__, ( 1.000/increment ) );
   DEBUG_PRINTF( "%s(): The curve will have %d points\n", 
         __func__, num_curve_points );

   Point curve_points[num_curve_points]; 
   int point_index = 0;

   for ( double t_index = 0.0; t_index <= 1.000; t_index += increment ) {
      DEBUG_PRINTF( "Point index %d: %12.3f\n", point_index, t_index );
      curve_points[point_index] = calc( t_index );
      point_index++;
   }

   int num_lines = this->num_lines;
   Point prev_end_point;
   
   this->lines[0].set_start_point( curve_points[0] );
   this->lines[0].set_end_point( curve_points[1] );

   DEBUG_PRINTF( "%s(): Line 0 is ", __func__ );
   DEBUG_FUNC( this->lines[0].display( ) ); 
   DEBUG_PRINTF( "\n" );
   
   // Copy the end point to be the next start point
   ulong end_x = curve_points[1].get_x( );
   ulong end_y = curve_points[1].get_y( );
   prev_end_point.set_x_y( end_x, end_y );
   
   for ( int line_index = 1; line_index < num_lines; line_index++ ) {
      this->lines[line_index].set_start_point( prev_end_point );
      this->lines[line_index].set_end_point( curve_points[line_index+1] );

      DEBUG_PRINTF( "%s(): Line %d is ", __func__, line_index );
      DEBUG_FUNC( this->lines[line_index].display( ) ); 
      DEBUG_PRINTF( "\n" );
      
      // Copy the end point to be the next start point
      ulong end_x = curve_points[line_index+1].get_x( );
      ulong end_y = curve_points[line_index+1].get_y( );
      prev_end_point.set_x_y( end_x, end_y );

   } // end of for ( int line_index = 1; line_index < num_lines; line_index++ )
}


int BezierCurve::binomial( int n_val, int k_val ) {
   VoV lut;
   while( n_val >= lut.size() ) {
      int lut_size = lut.size() ;
      vector<int> next_row(lut_size+1);
      next_row[0] = 1;
      int prev_size = lut_size - 1;
      for ( int index = 1; index < lut_size; index++ ) {
         next_row[index] = lut[prev_size][index-1] + 
            lut[prev_size][index];
      }
      next_row[lut_size] = 1;
      lut.push_back(next_row);
   }
   return lut[n_val][k_val];
}


Point BezierCurve::second_order_calc( double t_val ) {
   Point result;
   
   double t_squared = t_val * t_val;
   double mt = 1 - t_val;
   double mt_squared = mt * mt;
   
   DEBUG_PRINTF( "%s(): t = %12.6f\n", __func__, t_val );
   DEBUG_PRINTF( "%s(): t^2 = %12.6f\n", __func__, t_squared );
   DEBUG_PRINTF( "%s(): 1 - t = %12.6f\n", __func__, mt );
   DEBUG_PRINTF( "%s(): (1 - t)^2 = %12.6f\n", __func__, mt_squared );

   result = mt_squared * control_points[0] +
      ( 2 * mt * t_val ) * control_points[1] + 
      t_squared * control_points[2];

   DEBUG_PRINTF( "%s(): result point is ", __func__ );
   DEBUG_FUNC( result.display() );
   DEBUG_PRINTF( "\n" );
   return result;
}

Point BezierCurve::third_order_calc( double t_val ) {
   Point result;
   
   double t_squared = t_val * t_val;
   double t_cubed = t_squared * t_val;
   double mt = 1 - t_val;
   double mt_squared = mt * mt;
   double mt_cubed = mt_squared * mt;

   DEBUG_PRINTF( "%s(): t = %12.6f\n", __func__, t_val );
   DEBUG_PRINTF( "%s(): t^2 = %12.6f\n", __func__, t_squared );
   DEBUG_PRINTF( "%s(): t^3 = %12.6f\n", __func__, t_cubed );
   DEBUG_PRINTF( "%s(): 1 - t = %12.6f\n", __func__, mt );
   DEBUG_PRINTF( "%s(): (1 - t)^2 = %12.6f\n", __func__, mt_squared );
   DEBUG_PRINTF( "%s(): (1 - t)^3 = %12.6f\n", __func__, mt_cubed );
  
   result = mt_cubed * control_points[0] + 
      ( 2 * mt_squared * t_val ) * control_points[1] + 
      ( 3 * mt * t_squared ) * control_points[2] + 
      t_cubed * control_points[3];

   DEBUG_PRINTF( "%s(): result point is ", __func__ );
   DEBUG_FUNC( result.display() );
   DEBUG_PRINTF( "\n" );
   return result;
}

Point BezierCurve::n_order_calc( double t_val ) {
   Point result;
   result.set_x_y( 0, 0 );

   int order = this->order;
   int num_weights = this->order + 1;

   for ( int index = 0; index < order; index++ ) {
      int binomial_term = binomial(order,index);
      DEBUG_PRINTF( "%s(): index: %d binomial term is %d\n", __func__, 
         index, binomial_term );
      double first_poly_term = pow((double)(1-t_val),(double)(order-index));
      DEBUG_PRINTF( "%s(): index: %d first_poly_term is %12.3f\n", __func__, 
         index, first_poly_term );
      double second_poly_term = pow(t_val,(double)index);
      DEBUG_PRINTF( "%s(): index %d second_poly_term is %12.3f\n", __func__, 
         index, second_poly_term );
      DEBUG_PRINTF( "%s(): index %d control_point is ", __func__, 
         index );
      DEBUG_FUNC( control_points[index].display() );
      DEBUG_PRINTF( "\n" ); 

      result = result + control_points[index] * binomial_term 
         * first_poly_term * second_poly_term;

      DEBUG_PRINTF( "%s(): index %d result point is ", __func__, index );
      DEBUG_FUNC( result.display() );
      DEBUG_PRINTF( "\n" );
   }

   DEBUG_PRINTF( "%s(): result point is ", __func__ );
   DEBUG_FUNC( result.display() );
   DEBUG_PRINTF( "\n" );
   return result;
}

Point BezierCurve::calc( double t_val ) {
   int order = this->order;
   if ( order == 2 ) {
      return second_order_calc( t_val );
   } else if ( order == 3 ) {
      return third_order_calc( t_val );
   } else {
      return n_order_calc( t_val );
   }
}

