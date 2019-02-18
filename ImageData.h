#ifndef _IMAGEDATA_H_
#define _IMAGEDATA_H_

#include <string>
#include "util.h"

class ImageData {
   public:
      ImageData( ulong num_iterations, std::string filename, 
            ulong background_color );
      ImageData( ulong width, ulong height, std::string filename, 
            ulong background_color );
      ~ImageData( );
      
      void set_pixel( ulong idx, ulong val );
      void set_pixel( ulong x, ulong y, ulong val );
      void set_pixel( Point point, ulong val );
      void set_pixels( ulong* pixels ) { this->pixels = pixels; }

      void set_width( ulong width ) { this->width = width; }
      void set_height( ulong height ) { this->height = height; }
      void set_num_pixels( ulong num_pixels ) { 
         this->num_pixels = num_pixels; 
      }
      void set_filename( ulong filename ) { 
         this->filename = filename; 
      }
      void set_background_color( ulong background_color ) {
         this->background_color = background_color;
      }

      ulong* get_pixels( ) { return pixels; }
      ulong get_width( ) { return width; }
      ulong get_height( ) { return height; }
      ulong get_num_pixels( ) { return num_pixels; }
      ulong get_background_color( ) { return background_color; }
      std::string get_filename( ) { return filename; } 

   private:
      ulong* pixels;
      ulong width;
      ulong height;
      ulong num_pixels;
      ulong background_color;
      std::string filename;
};

#endif
