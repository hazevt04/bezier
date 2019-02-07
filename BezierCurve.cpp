// Implementation of BezierCurve Class

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "util.h"
#include "BezierCurve.h"

using std::vector;
using std::cout;
using std::endl;

typedef vector<vector<int>> VoV;

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
      int num_curve_points = 200 ) {
   
   this->order = order;
   
   this->control_points = control_points;
   this->num_curve_points = num_curve_points + 2;
   this->num_lines = num_curve_points;
   cout << __func__ << "(): num lines is " << this->num_lines << endl;
   this->lines = new Line[num_lines];
}

// Third order curve
void BezierCurve::generateCurve( ) {
   int num_curve_points = this->num_curve_points;
   double increment = 1.0/(double)num_curve_points;
   cout << __func__ << "(): increment is " << increment << endl;

   cout << __func__ << "(): t_index check- iterating from 0.0 to 1.000." 
      << endl;
   cout << __func__ << "(): There are " << ( 1.000/increment ) << " points."
      << endl;
   cout << __func__ << "(): num_curve_points is " << num_curve_points << endl;

   Point curve_points[num_curve_points]; 
   int point_index = 0;

   for ( double t_index = 0.0; t_index <= 1.000; t_index += increment ) {
      cout << "t_index is " << t_index << endl;
      cout << "Point index is " << point_index << endl;
      curve_points[point_index] = third_order_calc( t_index );
      point_index++;
   }

   /*
   int num_lines = this->num_lines;
   Point prev_end_point;
   
   this->lines[0].set_start_point( curve_points[0] );
   cout << "After this->lines[0].set_start_point( curve_points[0] )" << endl;
   this->lines[0].set_end_point( curve_points[1] );
   cout << "After this->lines[0].set_end_point( curve_points[1] )" << endl;
   
   // Copy the end point to be the next start point
   ulong end_x = curve_points[1].get_x( );
   ulong end_y = curve_points[1].get_y( );
   prev_end_point.set_x_y( end_x, end_y );

   for ( int line_index = 1; line_index < num_lines; line_index++ ) {
      this->lines[line_index].set_start_point( prev_end_point );
      this->lines[line_index].set_end_point( curve_points[line_index+1] );

      cout << __func__ << "(): line " << line_index << " is " 
         << this->lines[line_index].get_display_str( ) << endl;
      
      // Copy the end point to be the next start point
      ulong end_x = curve_points[line_index+1].get_x( );
      ulong end_y = curve_points[line_index+1].get_y( );
      prev_end_point.set_x_y( end_x, end_y );

      cout << __func__ << "(): index " << line_index 
         << ": prev_end_point is " << prev_end_point.get_display_str( ) 
         << endl;
   }
   */
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

double BezierCurve::n_order_calc( int num, double t_val, int weights[] ) {
   double sum = 0.0;
   for ( int index = 0; index < num; index++ ) {
      sum += weights[index] * binomial(num,index) * 
         (pow((double)(1-t_val),(double)(num-index))) * 
         (pow(t_val,(double)index));

      DEBUG_PRINTF( "%s(): %d, %d: sum is %12.6f\n", __func__, num, index, sum );
   }
   return sum;
}

double BezierCurve::second_order_calc( double t_val, int weights[] ) {
   double t_squared = t_val * t_val;
   double mt = 1 - t_val;
   double mt_squared = mt * mt;
   DEBUG_PRINTF( "%s(): t = %12.6f\n", __func__, t_val );
   DEBUG_PRINTF( "%s(): t^2 = %12.6f\n", __func__, t_squared );
   DEBUG_PRINTF( "%s(): 1 - t = %12.6f\n", __func__, mt );
   DEBUG_PRINTF( "%s(): (1 - t)^2 = %12.6f\n", __func__, mt_squared );
   DEBUG_PRINTF( "%s(): weights: { %d, %d, %d }\n", __func__,
         weights[0], weights[1], weights[2] );
   return mt_squared * weights[0] + 
      ( 2 * mt * t_val ) * weights[1] + 
      t_squared * weights[2];
}

double BezierCurve::third_order_calc( double t_val, int weights[] ) {
   double t_squared = t_val * t_val;
   double t_cubed = t_squared * t_val;
   double mt = 1- t_val;
   double mt_squared = mt * mt;
   double mt_cubed = mt_squared * mt;
   DEBUG_PRINTF( "%s(): t = %12.6f\n", __func__, t_val );
   DEBUG_PRINTF( "%s(): t^2 = %12.6f\n", __func__, t_squared );
   DEBUG_PRINTF( "%s(): t^3 = %12.6f\n", __func__, t_cubed );
   DEBUG_PRINTF( "%s(): 1 - t = %12.6f\n", __func__, mt );
   DEBUG_PRINTF( "%s(): (1 - t)^2 = %12.6f\n", __func__, mt_squared );
   DEBUG_PRINTF( "%s(): (1 - t)^3 = %12.6f\n", __func__, mt_cubed );
   DEBUG_PRINTF( "%s(): weights: { %d, %d, %d, %d }\n", __func__,
         weights[0], weights[1], weights[2], weights[3] );
   return mt_cubed * weights[0] + 
      ( 2 * mt_squared * t_val ) * weights[1] + 
      ( 3 * mt * t_squared ) * weights[2] + 
      t_cubed * weights[3];
}

Point BezierCurve::third_order_calc( double t_val ) {
   ulong x_result;
   ulong y_result;

   double t_squared = t_val * t_val;
   double t_cubed = t_squared * t_val;
   double mt = 1- t_val;
   double mt_squared = mt * mt;
   double mt_cubed = mt_squared * mt;
   DEBUG_PRINTF( "%s(): t = %12.6f\n", __func__, t_val );
   DEBUG_PRINTF( "%s(): t^2 = %12.6f\n", __func__, t_squared );
   DEBUG_PRINTF( "%s(): t^3 = %12.6f\n", __func__, t_cubed );
   DEBUG_PRINTF( "%s(): 1 - t = %12.6f\n", __func__, mt );
   DEBUG_PRINTF( "%s(): (1 - t)^2 = %12.6f\n", __func__, mt_squared );
   DEBUG_PRINTF( "%s(): (1 - t)^3 = %12.6f\n", __func__, mt_cubed );
   
   ulong x_weights[ 4 ];
   ulong y_weights[ 4 ];
   
   for ( int index = 0; index < 4; index++ ) {
      x_weights[index] = this->control_points[index].get_x();
      y_weights[index] = this->control_points[index].get_y();
   }

   DEBUG_PRINTF( "%s(): x_weights: { %lu, %lu, %lu, %lu }\n", __func__,
         x_weights[0], x_weights[1], x_weights[2], x_weights[3] );
   
   DEBUG_PRINTF( "%s(): y_weights: { %lu, %lu, %lu, %lu }\n", __func__,
         y_weights[0], y_weights[1], y_weights[2], y_weights[3] );
   
   x_result = mt_cubed * x_weights[0] + 
      ( 2 * mt_squared * t_val ) * x_weights[1] + 
      ( 3 * mt * t_squared ) * x_weights[2] + 
      t_cubed * x_weights[3];
   
   y_result = mt_cubed * y_weights[0] + 
      ( 2 * mt_squared * t_val ) * y_weights[1] + 
      ( 3 * mt * t_squared ) * y_weights[2] + 
      t_cubed * y_weights[3];

   Point result( x_result, y_result );
   //DEBUG_PRINTF( "%s(): result point is %s\n", result.get_display_str() );
   
   cout << __func__ << "(): result point is " << result.get_display_str()
      << endl;
   return result;
}



