#ifndef _LINEDRAWER_H_
#define _LINEDRAWER_H_

#include "Line.h"
#include "ImageData.h"

class LineDrawer {
   public:
      LineDrawer( ) { };
      ~LineDrawer( ) { };
      LineDrawer( ImageData* image_data ) { this-> image_data = image_data; }
      virtual void draw( Line* line ) = 0;
   protected:
      ImageData* image_data;
};


#endif
