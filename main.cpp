
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

using std::time_t;
using std::string;

int main( int argc, char* argv[] ) {
   
   int num_curve_points;
   if ( argc > 1 ) {
      num_curve_points = atoi( argv[1] );
   } else {
      num_curve_points = 200;
   }

   std::cout << "num_curve_points set to " << num_curve_points << std::endl;

   // Setup image data
   ulong width = 600;
   ulong height = 600;
   string filename = "bezier.png";
   ulong background_color = Util::WHITE;
   PNGImageData* image_data = new PNGImageData( width, height, filename, 
         background_color );
   BresenhamLineDrawer* line_drawer = new BresenhamLineDrawer( image_data );

   // Settings common for all the bezier curves here
   int order = 3;
   int num_control_points = order + 1;
   ulong curve_color = Util::BLACK;
   int num_lines = num_curve_points;
  
   int num_curves = 8;
   BezierCurve* bezier_curves = new BezierCurve[num_curves];
   ulong x_vals[num_control_points] = {
      120, 35, 220, 220
   };
   ulong y_vals[num_control_points] = {
      160, 200, 260, 40
   };
   Point control_points[num_curves][num_control_points];

   DEBUG_PRINTF( "There are %d control points.\n", num_control_points );
   DEBUG_PRINTF( "There are %d curves.\n", num_curves );
   DEBUG_PRINTF( "Each curve will have  %d  lines.\n", num_lines );

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
      
      DEBUG_PRINTF( "Curve %d: Generating Bezier curve of order %d.\n", curve_num, order );
      for ( int point_index = 0; point_index < num_control_points; point_index++ ) {
         DEBUG_PRINTF( "Curve %d: Control Point %d: ", curve_num, point_index );
         DEBUG_FUNC( control_points[curve_num][point_index].display() );
         DEBUG_PRINTF( "\n" );
      }

      start_time = clock();
      bezier_curves[curve_num].generate_curve( );
      duration = (double)( clock() - start_time )/
         (double)( CLOCKS_PER_SEC );
      DEBUG_PRINTF( "Curve %d: Bezier Curve Generation duration was %12.6f seconds.\n", 
            curve_num, duration );
      gen_curve_duration += duration;

      Line* bezier_lines = bezier_curves[curve_num].get_lines( );

      start_time = clock();
      for ( int line_num = 0; line_num < num_lines; line_num++ ) {
         if ( !bezier_lines[line_num].line_is_point() ) {
            line_drawer->draw( &bezier_lines[line_num] );
         }
      }
      duration = (double)( clock() - start_time )/
         (double)( CLOCKS_PER_SEC );
      DEBUG_PRINTF( "Curve %d: Bezier Curve Draw duration was %12.6f seconds.\n\n", 
            curve_num, duration );

      draw_curve_duration += duration;

      x_vals[1] += 20;
      y_vals[1] += 60;

      x_vals[2] += 20;
      y_vals[2] += 40;

      x_vals[3] += 20;
      y_vals[3] += 80;

   } // end of for ( int curve_num; curve_num < num_curves; curve_num++ ) {
   
   printf( "Bezier Curve Generate duration was %12.6f seconds for %d curves.\n", 
         gen_curve_duration, num_curves );
   printf( "Bezier Curve Draw duration was %12.6f seconds for %d curves.\n", 
         draw_curve_duration, num_curves );
   
   PNGRenderer* renderer = new PNGRenderer( image_data );

   start_time = clock();
   renderer->render( );
   double render_curve_duration = (double)( clock() - start_time )/
      (double)( CLOCKS_PER_SEC );
   printf( "Bezier Curve Render duration was %12.6f seconds.\n", render_curve_duration );
   
   double overall_duration = gen_curve_duration + draw_curve_duration + 
      render_curve_duration;
   printf( "Overall duration was %12.6f seconds.\n", overall_duration );

   printf( "Output curve is in %s\n", filename.c_str() );

   return 0;
}
