#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/sge.h>
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
    Uint32	  alpha;
    float	  scale,xscale,yscale,rotate;
    void          LoadBMP();
    void          LoadPNG();

    SDL_Surface   *workScreen; 
    SDL_Surface	  *tfScreen; 

};
 
};
