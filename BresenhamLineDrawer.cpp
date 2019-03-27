#include <stdio.h>
#include <cmath>

#include "Util.h"
#include "Line.h"
#include "PNGImageData.h"
#include "BresenhamLineDrawer.h"

void BresenhamLineDrawer::draw_vertical( Line* line ) {

   Point start_point = line->get_start_point( );
   Point end_point = line->get_end_point( );
   ulong color = line->get_color( );
   ulong x0 = start_point.get_x( );
   ulong y1 = end_point.get_y( );
   ulong y0 = start_point.get_y( );
   
   for ( ulong y = y0; y < y1; y++ ) {
      //this->image_data->set_pixel( x0, y, color );
      this->image_data->set_png_bytes( x0, y, color );
      DEBUG_PRINTF( "%s(): set_png_bytes(): y is %lu: x0 is %lu\n", 
            __func__, y, x0 );
   }
   DEBUG_PRINTF( "\n\n" );
}

void BresenhamLineDrawer::draw_horizontal( Line* line ) {

   Point start_point = line->get_start_point( );
   Point end_point = line->get_end_point( );
   ulong color = line->get_color( );
   ulong x1 = end_point.get_x( );
   ulong x0 = start_point.get_x( );
   ulong y0 = start_point.get_y( );

   DEBUG_PRINTF( "%s(): x0 is %lu\n", __func__, x0 );
   DEBUG_PRINTF( "%s(): x1 is %lu\n", __func__, x1 );
   for ( ulong x = x0; x < x1; x++ ) {
      this->image_data->set_png_bytes( x, y0, color );
      DEBUG_PRINTF( "%s(): set_png_bytes(): x is %lu: y0 is %lu\n", 
            __func__, x, y0 );
   }
   DEBUG_PRINTF( "\n\n" );
}

void BresenhamLineDrawer::draw_gradual( Line* line ) {

   Point start_point = line->get_start_point( );
   Point end_point = line->get_end_point( );
   ulong color = line->get_color( );
   ulong x1 = end_point.get_x( );
   ulong x0 = start_point.get_x( );
   ulong y1 = end_point.get_y( );
   ulong y0 = start_point.get_y( );

   long delta_x = x1 - x0;
   long delta_y = y1 - y0;
   long two_delta_y = delta_y << 1;
   long two_delta_x = delta_x << 1;
   long yi = 1;
   
   DEBUG_PRINTF( "%s(): delta_y is %ld\n", __func__, delta_y );
   DEBUG_PRINTF( "%s(): delta_x is %ld\n", __func__, delta_x );
   DEBUG_PRINTF( "%s(): two_delta_y is %ld\n", __func__, two_delta_y );
   DEBUG_PRINTF( "%s(): two_delta_x is %ld\n", __func__, two_delta_x );
   DEBUG_PRINTF( "%s(): color is %lu\n", __func__, color );
   
   if ( delta_y < 0 ) {
      yi = -1;
      delta_y = -delta_y;
      two_delta_y = -two_delta_y;
      DEBUG_PRINTF( "%s(): yi changed to %ld\n", __func__, yi );
      DEBUG_PRINTF( "%s(): delta_y changed to %ld\n", __func__, delta_y );
      DEBUG_PRINTF( "%s(): two_delta_y changed to %ld\n", __func__, two_delta_y );
   }
   long delta_upper = two_delta_y - delta_x;
   DEBUG_PRINTF( "%s(): delta_upper is %ld\n", __func__, delta_upper );
   ulong y = y0;

   for ( ulong x = x0; x <= x1; x++ ) {
      //this->image_data->set_pixel( x, y, color );
      this->image_data->set_png_bytes( x, y, color );
      DEBUG_PRINTF( "%s(): set_png_bytes(): x is %lu: y is %lu\n", __func__, x, y );

      // TODO: Get rid of branch
      if ( delta_upper > 0 ) {
         y += yi;
         delta_upper -= two_delta_x;
      
         DEBUG_PRINTF( "%s(): x is %lu: y changed to %lu\n", __func__, x, y );
         DEBUG_PRINTF( "%s(): x is %lu: delta_upper changed to %ld\n", __func__, 
            x, delta_upper );

      }
      delta_upper += two_delta_y;
      DEBUG_PRINTF( "%s(): x is %lu: delta_upper changed to %ld\n", __func__, 
         x, delta_upper );
      
   } // end of for ( ulong index = x0; index < x1; index++ ) {
   DEBUG_PRINTF( "\n\n" );
}


void BresenhamLineDrawer::draw_steep( Line* line ) {

   Point start_point = line->get_start_point( );
   Point end_point = line->get_end_point( );
   ulong color = line->get_color( );
   ulong x1 = end_point.get_x( );
   ulong x0 = start_point.get_x( );
   ulong y1 = end_point.get_y( );
   ulong y0 = start_point.get_y( );

   long delta_x = x1 - x0;
   long delta_y = y1 - y0;
   long two_delta_y = delta_y << 1;
   long two_delta_x = delta_x << 1;
   long xi = 1;
   
   DEBUG_PRINTF( "%s(): Start Point is (x0: %lu, y0: %lu)\n", __func__, x0, y0 );
   DEBUG_PRINTF( "%s(): End Point is (x1: %lu, y1: %lu)\n", __func__, x1, y1 );
   DEBUG_PRINTF( "%s(): delta_x is %ld\n", __func__, delta_x );
   DEBUG_PRINTF( "%s(): delta_y is %ld\n", __func__, delta_y );
   DEBUG_PRINTF( "%s(): xi is %ld\n", __func__, xi );

   DEBUG_PRINTF( "%s(): two_delta_x is %ld\n", __func__, two_delta_x );
   DEBUG_PRINTF( "%s(): two_delta_y is %ld\n", __func__, two_delta_y );
   DEBUG_PRINTF( "%s(): color is %lu\n", __func__, color );
   
   if ( delta_x < 0 ) {
      xi = -1;
      delta_x = -delta_x;
      two_delta_x = -two_delta_x;
      DEBUG_PRINTF( "%s(): xi changed to %ld\n", __func__, xi );
      DEBUG_PRINTF( "%s(): delta_x changed to %ld\n", __func__, delta_x );
      DEBUG_PRINTF( "%s(): two_delta_x changed to %ld\n", __func__, two_delta_x );
   }

   long delta_upper = two_delta_x - delta_y;
   ulong x = x0;
   DEBUG_PRINTF( "%s(): delta_upper is %ld\n", __func__, delta_upper );
   DEBUG_PRINTF( "%s(): x is %lu\n", __func__, x );

   for ( ulong y = y0; y <= y1; y++ ) {
      //this->image_data->set_pixel( x, y, color );
      this->image_data->set_png_bytes( x, y, color );
      DEBUG_PRINTF( "%s(): set_png_bytes(): y is %lu: x is %lu\n", __func__, y, x );

      // TODO: Get rid of branch
      if ( delta_upper > 0 ) {
         x += xi;
         delta_upper -= two_delta_y;
      
         DEBUG_PRINTF( "%s(): y is %lu: x changed to %lu\n", __func__, y, x );
         DEBUG_PRINTF( "%s(): y is %lu: delta_upper changed to %ld\n", __func__, 
            y, delta_upper );

      }
      delta_upper += two_delta_x;
      DEBUG_PRINTF( "%s(): y is %lu: delta_upper changed to %ld\n", __func__, 
         y, delta_upper );
      
   } // end of for ( ulong y = y0; y < y1; y++ ) {

   DEBUG_PRINTF( "\n\n" );
}

void BresenhamLineDrawer::draw( Line* line ) {

   Point start_point = line->get_start_point( );
   Point end_point = line->get_end_point( );
   ulong color = line->get_color( );
   ulong x1 = end_point.get_x( );
   ulong x0 = start_point.get_x( );
   ulong y1 = end_point.get_y( );
   ulong y0 = start_point.get_y( );
   
   DEBUG_PRINTF( "%s(): Start Point is (x0: %lu, y0: %lu)\n", __func__, x0, y0 );
   DEBUG_PRINTF( "%s(): End Point is (x1: %lu, y1: %lu)\n", __func__, x1, y1 );
   Line* reversed_line = new Line( &end_point, &start_point, color );
   DEBUG_PRINTF( "%s(): Reversed line display\n", __func__ );
   DEBUG_FUNC( reversed_line->display() );

   if ( ( y1 == y0 ) && ( x1 != x0 ) ) {
      if ( x0 > x1 ) {
         draw_horizontal( reversed_line );
      } else {
         draw_horizontal( line );
      }
   } else if ( ( x1 == x0 ) && ( y1 != y0 ) ) {
      if ( y0 > y1 ) {
         draw_vertical( reversed_line );
      } else {
         draw_vertical( line );
      }
   } else {
      if ( abs( y1 - y0 ) <= abs( x1 - x0 ) ) {
         if ( x0 > x1 ) {
            draw_gradual( reversed_line );
         } else {
            draw_gradual( line );
         }
      } else {
         if ( y0 > y1 ) {
            draw_steep( reversed_line );
         } else {
            draw_steep( line );
         }
      } // end of if ( abs( y1- y0 ) < abs( x1 - x0 ) ) {
   } // end of if ( ( y1 == y0 ) && ( x1 != x0 ) ) {
   
   delete reversed_line;
}



