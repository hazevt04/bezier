
#include <iostream>
#include <ctime>

#include "util.h"
#include "BezierCurve.h"

using std::cout;
using std::endl;
using std::time_t;

int main( int argc, char* argv[] ) {
   double result;

   int x_values[] = { 120, 35, 220, 220 };
   int y_values[] = { 160, 200, 260, 40 };

   double x_results[ 201 ];
   double y_results[ 201 ];

   BezierCurve* bezier = new BezierCurve(); 
   
   clock_t start_time = clock();
   int scaled_index = 0;
   for ( double t_index = 0.0; t_index <= 1.005; t_index += 0.005 ) {
      x_results[ scaled_index ] = bezier->third_order_calc( t_index, x_values );
      
      DEBUG_PRINTF( "bezier_order_3( %12.6f, x ) is %12.6f\n",
           t_index, x_results[ scaled_index ] ); 
      y_results[ scaled_index ] = bezier->third_order_calc( t_index, y_values );
      DEBUG_PRINTF( "bezier_order_3( %12.6f, y ) is %12.6f\n",
           t_index, y_results[ scaled_index ] ); 
      scaled_index++;
   }
   DEBUG_PRINTF( "\n" );

   double duration = (double)( clock() - start_time )/
      (double)( CLOCKS_PER_SEC );
   
   cout << "Overall duration was " << duration 
      << " seconds." << endl;
   cout << endl;

   delete bezier;
   return 0;
}
