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
    Uint32	  rotate, alpha;
    float	  scale,xscale,yscale;
    void          LoadBMP();
    void          LoadPNG();

    void          RotatePicture (SDL_Surface *screen, 
				 SDL_Surface *picture, 
				 int rotate, int smooth);
 
    void          ZoomPicture (SDL_Surface *screen, 
			       SDL_Surface *picture, 
			       int smooth, float zoomxf, float zoomyf); 

};
 
};
