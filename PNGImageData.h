#ifndef _PNGIMAGEDATA_H_
#define _PNGIMAGEDATA_H_

#include <string>
#include "png.h"
#include "ImageData.h"
#include "Util.h"

class PNGImageData : public ImageData {
   public:
      PNGImageData( ulong num_iterations, std::string filename, 
            ulong background_color );
      PNGImageData( ulong width, ulong height, std::string filename, 
            ulong background_color );
      ~PNGImageData();
      
      void set_png_bytes( ulong idx, ulong val ); 
      void set_png_bytes( ulong x, ulong y, ulong val ); 
      void set_png_rows( png_byte** png_rows ) { this->png_rows = png_rows; }

      png_byte** get_png_rows( ) { return this->png_rows; }
   private:
      
      png_byte** png_rows;
      ulong num_png_row_bytes;

};

#endif
