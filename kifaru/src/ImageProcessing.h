#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "config.h"
#include "primitives.h"
#include "tools.h"
#include "SDL_rotozoom.h"
#include "SDL_gfxPrimitives.h"


namespace ephidrena{

class Image : public Effect
{
 private:
     SDL_Surface  *pic;   
 public:
     Image();
    ~Image();
    void          Init(AttrMap);
    void          Render(SDL_Surface*);
    SDL_Surface*  Scale(SDL_Surface*, float, float);
    Uint32        xofs,yofs;
    float	  scale,xscale,yscale;
    Uint32	  rotate;
    void          LoadBMP();
    void          LoadPNG();

    void          RotatePicture (SDL_Surface *screen, 
				 SDL_Surface *picture, 
				 int rotate, int smooth);
 
    void          ZoomPicture (SDL_Surface *screen, 
			       SDL_Surface *picture, 
			       int smooth, float zoomxf, float zoomyf); 

    void          Draw (SDL_Surface *screen);
};
 
};
