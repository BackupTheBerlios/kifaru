#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "config.h"
#include "primitives.h"
#include "inits.h"
#include "EffectFactory.h"

#include "effect.h"

using namespace std;

namespace ephidrena
{
    
    SDL_Surface *morn;

Image::Image()
    : Effect("Image")
{
    
     
    xofs=0;
    yofs=0;
}

Image::~Image()
{
    
}    

void Image::Render (SDL_Surface *screen)
{
        SDL_Rect dest;
        dest.x = xofs;
        dest.y = yofs;
        SDL_BlitSurface(this->pic, NULL, screen, &dest);
        return;
}

void Image::LoadBMP()
{
     this->pic=SDL_LoadBMP(fileName); 
     cout << "image loaded" << endl;
             
}  

void Image::LoadPNG()
{
    SDL_RWops *rwop;
    rwop = SDL_RWFromFile(fileName, "rb");
    this->pic=IMG_LoadPNG_RW(rwop);
    if(!this->pic) cout << "LoadPNG tryna!" << endl;
}

SDL_Surface* Image::Scale(SDL_Surface *original, float xscale, float yscale)
{
    Uint32 xofs = 0, yofs = 0, dofs = 0;
    float sofs = 0, sinc = 1 / xscale, sy = 0;
    Uint32 *pixels;
    SDL_Surface *scaled = SDL_CreateRGBSurface(SDL_SWSURFACE,
          (xscale * original->w), (yscale * original->h), original->format->BitsPerPixel,
          original->format->Rmask, original->format->Gmask , original->format->Bmask, original->format->Amask);

     Uint32 *original_pixels = static_cast<Uint32 *>(original->pixels);
     Uint32 *scaled_pixels  = static_cast<Uint32 *>(scaled->pixels);
     while(yofs < (yscale * original->h))
     {
        while(xofs < (xscale * original->w))
        {
            scaled_pixels[dofs] = original_pixels[(Uint32)sofs];
            dofs++;
            sofs += sinc;
        }

        sy += 1 / yscale;
        sofs = sy * original->pitch;
      }

}

Effect::Effect(const char *name)
    : m_name(name)
{
    return;
}  

Effect::~Effect()
{
    return;
}

void Effect::Render(SDL_Surface *screen)
{
    
}

void Effect::prepare()
{

    
}

int Effect::ticks()
{
    
    return Ticks;

}

void Effect::newTick(Uint32 ticks)
{

}

bool Effect::isDone(Uint32 _ticks)
{
    return _ticks > this->Ticks;
}

void Effect::LoadPNG()
{
    
}

void Effect::LoadBMP()
{
    
}
            


void Effect::SLock(SDL_Surface *screen)
{
    if ( SDL_MUSTLOCK(screen) )
    {
        if (SDL_LockSurface(screen) < 0) return;
    }
}
            
void Effect::SULock(SDL_Surface *screen)
{
    if ( SDL_MUSTLOCK(screen) ) SDL_UnlockSurface(screen);
}


Jall::Jall()
    : Effect("Jall")
{

}

Jall::~Jall()
{

}


void Jall::Render(SDL_Surface *screen)
{
    static float XSin=0,YSin=0;
    static Uint8 vri=11;
    static float vreng=53;
    static Uint8 xs,ys;
    static Uint8 t;
    Uint32 x,y;
    
    SLock(screen);
    
    for( y=0; y<screen->h; y++ )
    {
        for ( x=0; x<screen->w; x++ )
        {
            t = vri+x+(y*ys);
            PutPixel(screen,x, y, t/3,t/2,t/2);   
        }
        YSin += 0.7;
            if (YSin > 1) YSin = -1;
            ys = Uint8(sin (YSin)  );

        //if (vri >= 255) vri=1;
        vri++;
        
        vreng+=0.7;

        //if (vreng >=256 ) vri=1;
    
    XSin+=0.13;
    YSin+=0.15;
 
    }        
    
     SULock(screen);
 
         
   
}    

Jull::Jull()
    : Effect("Jull")
{

}

Jull::~Jull()
{

}


void Jull::Render(SDL_Surface *screen)
{
    static float XSin=0,YSin=0;
    static Uint8 vri=11;
    static float vreng=53;
    static Uint8 xs,ys;
    static Uint8 t;
    Uint32 x,y;
    
    SLock(screen);
    
    for( y=0; y<screen->h; y++ )
    {
        for ( x=0; x<screen->w; x++ )
        {
            t = vri+x+(y*ys);
            PutPixel(screen,x, y, t/2,t/3,t/4);   
        }
        YSin += 0.7;
            if (YSin > 1) YSin = -1;
            ys = Uint8(sin (YSin)  );

        //if (vri >= 255) vri=1;
        vri++;
        
        vreng+=0.7;

        //if (vreng >=256 ) vri=1;
    
    XSin+=0.13;
    YSin+=0.15;
 
    }        
    
     SULock(screen);
 
         
   
}    

REGISTER_EFFECT(Image);
REGISTER_EFFECT(Jall);
REGISTER_EFFECT(Jull);
};
