
#include <iostream>
#include <ctime>

#include "util.h"
#include "Point.h"
#include "BezierCurve.h"

using std::cout;
using std::endl;
using std::time_t;

int main( int argc, char* argv[] ) {
   double result;

   int order = 3;
   Point* control_points = new Point[(order+1)];
   
   control_points[0].set_x_y( 120, 160 );
   control_points[1].set_x_y( 35, 200 );
   control_points[2].set_x_y( 220, 260 );
   control_points[3].set_x_y( 220, 40 );

   BezierCurve* bezier_curve = new BezierCurve( order, control_points, 201 ); 
   
   clock_t start_time = clock();

   bezier_curve->generateCurve( );
   
   double duration = (double)( clock() - start_time )/
      (double)( CLOCKS_PER_SEC );
   
   cout << "Overall duration was " << duration 
      << " seconds." << endl;
   cout << endl;

   return 0;
}
