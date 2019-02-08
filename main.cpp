
#include <iostream>
#include <ctime>
#include <string>

#include "util.h"
#include "Point.h"
#include "Line.h"
#include "BezierCurve.h"
#include "ImageData.h"
#include "BresenhamLineDrawer.h"
#include "PNGRenderer.h"

using std::cout;
using std::endl;
using std::time_t;
using std::string;

int main( int argc, char* argv[] ) {
   double result;

   int order = 3;
   Point* control_points = new Point[(order+1)];
   
   control_points[0].set_x_y( 120, 160 );
   control_points[1].set_x_y( 35, 200 );
   control_points[2].set_x_y( 220, 260 );
   control_points[3].set_x_y( 220, 40 );
   
   ulong color = Util::BLACK;

   BezierCurve* bezier_curve = new BezierCurve( order, control_points, 
      201, color  ); 
   
   clock_t start_time = clock();
   bezier_curve->generate_curve( );
   double gen_curve_duration = (double)( clock() - start_time )/
      (double)( CLOCKS_PER_SEC );
   cout << "Bezier Curve Generation duration was " << gen_curve_duration 
      << " seconds." << endl;
   cout << endl;

   Line* bezier_lines = bezier_curve->get_lines( );
   int num_lines = bezier_curve->get_num_lines( );

   // Setup image data
   ulong width = 600;
   ulong height = 600;
   string filename = "bezier.png";
   ulong background_color = Util::WHITE;
   ImageData* image_data = new ImageData( width, height, filename, 
         background_color );

   BresenhamLineDrawer* line_drawer = new BresenhamLineDrawer( image_data );
   
   start_time = clock();
   for ( int line_num = 0; line_num < num_lines; line_num++ ) {
      line_drawer->draw( &bezier_lines[ line_num ] );
   }
   double draw_curve_duration = (double)( clock() - start_time )/
      (double)( CLOCKS_PER_SEC );
   cout << "Bezier Curve Draw duration was " << draw_curve_duration 
      << " seconds." << endl;
   cout << endl;
   
   PNGRenderer* renderer = new PNGRenderer( image_data );
   start_time = clock();
   renderer->render( );


   double render_curve_duration = (double)( clock() - start_time )/
      (double)( CLOCKS_PER_SEC );
   cout << "Bezier Curve Render duration was " << render_curve_duration 
      << " seconds." << endl;
   cout << endl;
   
   double overall_duration = gen_curve_duration + draw_curve_duration + 
      render_curve_duration;
   cout << "Overall duration was " << overall_duration 
      << " seconds." << endl;
   cout << endl;

   return 0;
}
