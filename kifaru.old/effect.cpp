#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_Image.h>

#include "primitives.h"
#include "inits.h"

#include "effect.h"

#define MAX_TEXTURE_SIZE_X 256
#define MAX_TEXTURE_SIZE_Y 256

using namespace std;

namespace ephidrena
{
    
    SDL_Surface *morn;

Image::Image()
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
        dest.x = this->xofs;
        dest.y = this->yofs;
        SDL_BlitSurface(this->pic, NULL, screen, &dest);
        return;
}

SDL_Surface* Image::Scale (SDL_Surface *texture, Uint32 destSizeX, Uint32 destSizeY)
{
    SDL_Surface *scaled_texture;
    Uint32 ytable[MAX_TEXTURE_SIZE_Y];
    Uint32 ofs;
    float srcX=0,srcY=0;
    float xstep,ystep,step;
    Uint32 dstX=0,dstY=0;
    
    if (destSizeX == 0 || destSizeY == 0) return NULL;

    PreScale(texture, ytable);
    
    xstep = float(MAX_TEXTURE_SIZE_X / destSizeX);
    ystep = float(MAX_TEXTURE_SIZE_Y / destSizeY);

    for (dstY=0; dstY < destSizeY; dstY++)   
    {
        for (dstX = 0; dstX < destSizeX; dstX++;)
        {
        ofs =  Uint32(srcX) + ytable[Uint32(srcY)];
        srcX += xstep;

        texture[ofs+
        }
                    
        srcY += ystep;
    }        
    return scaled_texture;
}

void Image::PreScale (SDL_Surface* texture, Uint32* ytable)
{
    Uint32 i=0;
    
    while ( i < MAX_TEXTURE_SIZE_Y )
    {
        ytable[i] = (i * texture->pitch);
        i++;
    }    
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

Effect::Effect()
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

};
