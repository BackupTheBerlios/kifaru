#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>

using namespace std;

namespace ephidrena {

void EPH_SDL_Init();
void PutPixel(SDL_Surface *screen, Uint32 x, Uint32 y, Uint8 R, Uint8 G, Uint8 B);
void Plasma(SDL_Surface *screen);
void WriteNextPixel(SDL_Surface *screen, Uint32 offset, Uint8 R, Uint8 G, Uint8 B);
void Slock(SDL_Surface *screen);
void Sulock(SDL_Surface *screen);

void Plasma(SDL_Surface *screen)
{
    static float XSin=0,YSin=0;
    static Uint8 vri=11;
    static float vreng=53;
    static Uint8 xs,ys;
    static Uint8 t;
    Uint32 x,y;
    
    Slock(screen);
    
    for( y=0; y<screen->h; y++ )
    {
        for ( x=0; x<screen->w; x++ )
        {
            t = vri+x+y;
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
    
     Sulock(screen);
 
         
   
}    

void PutPixel(SDL_Surface *screen, Uint32 x, Uint32 y, Uint8 R, Uint8 G, Uint8 B)
{
     register Uint32 color = SDL_MapRGB(screen->format, R, G, B);
     register Uint32 *bufp;
     bufp = (Uint32 *)screen->pixels +y*screen->pitch/4 + x;
     *bufp = color;
}    

void WriteNextPixel(SDL_Surface *screen, Uint32 offset, Uint8 R, Uint8 G, Uint8 B)
{
    static Uint32 *bufp=0;
    Uint32 color =  ( R << 24 | G << 16 | B << 8 | 0 << 0 ) ;

    bufp = (Uint32 *)screen->pixels + offset;
    *bufp = color;
}
    
void Slock(SDL_Surface *screen)
{
    if ( SDL_MUSTLOCK(screen) )
    {
        if (SDL_LockSurface(screen) < 0) return;
    }
}
            
void Sulock(SDL_Surface * screen)
{
    if ( SDL_MUSTLOCK(screen) ) SDL_UnlockSurface(screen);
}

};
