
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
   int num_control_points = order + 1;
   Point* control_points = new Point[num_control_points];
   
   control_points[0].set_x_y( 120, 160 );
   control_points[1].set_x_y( 35, 200 );
   control_points[2].set_x_y( 220, 260 );
   control_points[3].set_x_y( 220, 40 );
   
   ulong curve_color = Util::BLACK;

   int num_curve_points = 1001;
   BezierCurve* bezier_curve = new BezierCurve( order, control_points, 
      num_curve_points, curve_color  ); 
   
   cout << "Generating Bezier curve of order " << order << "." << endl;
   cout << "There are " << num_control_points << " control points." << endl;
   for ( int point_index = 0; point_index < num_control_points; point_index++ ) {
      cout << "Control Point " << point_index << ": "; 
      control_points[point_index].display( );
      cout << endl;
   }
   cout << endl;

   clock_t start_time = clock();
   bezier_curve->generate_curve( );
   double gen_curve_duration = (double)( clock() - start_time )/
      (double)( CLOCKS_PER_SEC );
   cout << "Bezier Curve Generation duration was " << gen_curve_duration 
      << " seconds." << endl;

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
   
   PNGRenderer* renderer = new PNGRenderer( image_data );
   start_time = clock();
   renderer->render( );

   double render_curve_duration = (double)( clock() - start_time )/
      (double)( CLOCKS_PER_SEC );
   cout << "Bezier Curve Render duration was " << render_curve_duration 
      << " seconds." << endl;
   
   double overall_duration = gen_curve_duration + draw_curve_duration + 
      render_curve_duration;
   cout << "Overall duration was " << overall_duration 
      << " seconds." << endl;

   cout << "Output curve is in " << filename << endl;
   return 0;
}
