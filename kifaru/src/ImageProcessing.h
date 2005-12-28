#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/sge.h>
#include "config.h"
#include "primitives.h"
#include "tools.h"
//#include "SDL_rotozoom.h"
//#include "SDL_gfxPrimitives.h"


namespace ephidrena{

class Image : public Effect
{
    const char *    m_name;
 private:
    Uint32        xofs,yofs;
    Uint32	  alpha;
    bool	  hasAlpha;
    float	  scale,xscale,yscale,rotate;
    SDL_Surface   *workScreen; 
    SDL_Surface	  *tfScreen; 
 
 public:
    Image();
    ~Image();
    bool          Init(AttrMap);
    void          Render(SDL_Surface*);
    void          LoadBMP();
    void          LoadPNG();
    SDL_Surface   *pic;   


};
 
};
