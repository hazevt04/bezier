// Implementation of BezierCurve Class

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "util.h"
#include "BezierCurve.h"

typedef vector<vector<int>> VoV;

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
