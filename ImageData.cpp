#include "ImageData.h"

ImageData::ImageData( ulong num_iterations,
      std::string filename, 
      ulong background_color = 0 ) { 
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

}

ImageData::ImageData( ulong width, ulong height, 
      std::string filename, ulong background_color = 0 ) {
   
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
}

ImageData::~ImageData() {
   if (this->pixels) {
      delete [] this->pixels;
   }
}

void ImageData::set_pixel( ulong index, ulong val ) {
   if ( index < this->num_pixels ) {
      if ( this->pixels ) {
         pixels[ index ] = val;
      }
   }
}

void ImageData::set_pixel( Point point, ulong val ) {
   ulong x = point.get_x( );
   ulong y = point.get_y( );
   if ( ( x < this->width )  && ( y < this->height ) ) {
      if ( this->pixels ) {
         pixels[ ( y * this->width ) + x ] = val;
      }
   }
}

void ImageData::set_pixel( ulong x, ulong y, ulong val ) {
   if ( ( x < this->width )  && ( y < this->height ) ) {
      if ( this->pixels ) {
         pixels[ ( y * this->width ) + x ] = val;
      }
   }
}
