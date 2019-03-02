#include <string.h>
#include "PNGImageData.h"

PNGImageData::PNGImageData( ulong num_iterations,
      std::string filename, 
      ulong background_color = 0 ) : ImageData( num_iterations, filename, background_color ) { 
   ulong height;
   ulong width;
   ulong num_pixels;
   if ( num_iterations > 23 ) {
      width = 16530;
      height = 16530;
   } else {
      width = 8192;
      height = 8192;
   }
   num_pixels = width * height;
   
   this->width = width;
   this->height = height;
   this->pixels = new ulong[num_pixels];
   this->num_pixels = num_pixels;
   this->background_color = background_color;
   if ( this->pixels ) {
      for ( ulong index = 0; index < num_pixels; index++ ) {
         pixels[ index ] = background_color;
      }
   }
   this->filename = filename;
 
   ulong num_png_row_bytes = width * 3;
   this->png_rows = new png_byte*[height];
   if ( this->png_rows ) {
      for ( int y=0; y < height; y++ ) {
         this->png_rows[y] = new png_byte[num_png_row_bytes];
         memset( this->png_rows[y], Util::WHITE, num_png_row_bytes );
      }
   }

}

PNGImageData::PNGImageData( ulong width, ulong height, 
      std::string filename, ulong background_color = 0 ) : ImageData( width, height, filename, background_color ) {
   
   ulong num_pixels = width * height;

   this->width = width;
   this->height = height;
   this->num_pixels = width * height;
   this->pixels = new ulong[num_pixels];
   this->filename = filename;
   this->background_color = background_color;
   if ( this->pixels ) {
      for ( ulong index = 0; index < num_pixels; index++ ) {
         pixels[ index ] = background_color;
      }
   }

   ulong num_png_row_bytes = width * 3;
   ulong white = Util::WHITE;
   this->png_rows = new png_byte*[height];
   if ( this->png_rows ) {
      for ( int y=0; y < height; y++ ) {
         this->png_rows[y] = new png_byte[num_png_row_bytes];
         memset( this->png_rows[y], Util::WHITE, num_png_row_bytes );
      }
   } // end of if ( this->png_rows ) {
}

PNGImageData::~PNGImageData() {
   if (this->pixels) {
      delete [] this->pixels;
   }
   if ( this->png_rows ) {
      for ( int y = 0; y < height; y++ ) {
         if ( this->png_rows[y] ) {
            delete this->png_rows[y];
         }
      } // end of for ( int y = 0; y < height y++ )
      delete this->png_rows;
   }  
   
}

void PNGImageData::set_png_bytes( ulong idx, ulong val ) {
   ulong y = idx/this->width;
   ulong x = idx % this->width;
   if ( ( x < this->width )  && ( y < this->height ) ) {
      if ( this->png_rows[y] ) {
         memcpy( &(this->png_rows[y][x * 3]), &val, 3 );
      }
   }
}

void PNGImageData::set_png_bytes( ulong x, ulong y, ulong val ) {
   if ( ( x < this->width )  && ( y < this->height ) ) {
      if ( this->png_rows[y] ) {
         memcpy( &(this->png_rows[y][x * 3]), &val, 3 );
      }
   }
}
