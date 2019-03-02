#ifndef _BRESENHAMLINEDRAWER_H_
#define _BRESENHAMLINEDRAWER_H_

#include "Line.h"
#include "LineDrawer.h"
#include "PNGImageData.h"

class BresenhamLineDrawer: public LineDrawer {
   public:
      BresenhamLineDrawer( ) { };
      ~BresenhamLineDrawer( ) { };
      BresenhamLineDrawer( PNGImageData* image_data ) { 
         this->image_data = image_data;
      }
      PNGImageData* get_image_data( ) { return this->image_data; }
      void draw( Line* line );
   protected:
      void draw_steep( Line* line );
      void draw_steep_reversed( Line* line );
      void draw_gradual( Line* line );
      void draw_vertical( Line* line );
      void draw_horizontal( Line* line );
      PNGImageData* image_data;      
};


#endif
