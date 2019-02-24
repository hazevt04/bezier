
#include <iostream>
#include <ctime>
#include <string>

#include "Util.h"
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
   // Setup image data
   ulong width = 600;
   ulong height = 600;
   string filename = "bezier.png";
   ulong background_color = Util::WHITE;
   ImageData* image_data = new ImageData( width, height, filename, 
         background_color );
   BresenhamLineDrawer* line_drawer = new BresenhamLineDrawer( image_data );

   // Settings common for all the bezier curves here
   int order = 3;
   int num_control_points = order + 1;
   ulong curve_color = Util::BLACK;
   int num_curve_points = 1000;
  
   int num_curves = 4;
   BezierCurve* bezier_curves = new BezierCurve[num_curves];
   ulong x_vals[num_control_points] = {
      120, 35, 220, 220
   };
   ulong y_vals[num_control_points] = {
      160, 200, 260, 40
   };
   Point control_points[num_curves][num_control_points];

   cout << "There are " << num_control_points << " control points." << endl;
   cout << "There are " << num_curves << " curves." << endl;

   clock_t start_time;
   double duration = 0.0;
   double gen_curve_duration = 0.0;
   double draw_curve_duration = 0.0;
   for ( int curve_num = 0; curve_num < num_curves; curve_num++ ) {
      control_points[curve_num][0].set_x_y( x_vals[0], y_vals[0] );
      control_points[curve_num][1].set_x_y( x_vals[1], y_vals[1] );
      control_points[curve_num][2].set_x_y( x_vals[2], y_vals[2] );
      control_points[curve_num][3].set_x_y( x_vals[3], y_vals[3] );
      
      bezier_curves[curve_num].set_properties( order, &control_points[curve_num][0], 
         num_curve_points, curve_color  ); 
      
      cout << "Curve " << curve_num << ": Generating Bezier curve of order " 
         << order << "." << endl;
      for ( int point_index = 0; point_index < num_control_points; point_index++ ) {
         cout << "Curve " << curve_num << ": Control Point " 
            << point_index << ": " << control_points[point_index] << endl;
      }
      cout << endl;

      start_time = clock();
      bezier_curves[curve_num].generate_curve( );
      duration = (double)( clock() - start_time )/
         (double)( CLOCKS_PER_SEC );
      cout << "Curve: " << curve_num << ": Bezier Curve Generation duration was " 
         << duration 
         << " seconds." << endl;
      gen_curve_duration += duration;

      Line* bezier_lines = bezier_curves[curve_num].get_lines( );
      int num_lines = bezier_curves[curve_num].get_num_lines( );

      start_time = clock();
      for ( int line_num = 0; line_num < num_lines; line_num++ ) {
         line_drawer->draw( bezier_lines );
      }
      duration = (double)( clock() - start_time )/
         (double)( CLOCKS_PER_SEC );
      cout << "Curve " << curve_num <<": Bezier Curve Draw duration was " 
         << duration 
         << " seconds." << endl;
      draw_curve_duration += duration;

      x_vals[1] += 20;
      y_vals[1] += 60;

      x_vals[2] += 20;
      y_vals[2] += 40;

      x_vals[3] += 20;
      y_vals[3] += 80;

   } // end of for ( int curve_num; curve_num < num_curves; curve_num++ ) {
   
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
