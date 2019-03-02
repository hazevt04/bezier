#ifndef _PNGRENDERER_H_
#define _PNGRENDERER_H_

#include <iostream>
#include <string>

#include <stdio.h>
#include <png.h>

#include "PNGImageData.h"
#include "Renderer.h"

#include "Util.h"

class PNGRenderer : public Renderer {
   public:
      PNGRenderer() { };
      PNGRenderer( PNGImageData* image_data );
      ~PNGRenderer( );
      void render(); 
      void set_rgb( png_byte* ptr, ulong val );
      int write_png( char* title );
   private:
      png_structp png_ptr;
      png_infop info_ptr;
      png_bytep row;
      PNGImageData* image_data;
      FILE* fp;
            
};

#endif

