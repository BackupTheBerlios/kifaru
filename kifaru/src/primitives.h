#include <SDL/SDL.h>

namespace ephidrena
{
    
        
void PutPixel(SDL_Surface *screen,Uint32 x, Uint32 y, Uint8 R, Uint8 G, Uint8 B);
void Plasma(SDL_Surface *screen);
void WriteNextPixel(SDL_Surface *screen, Uint32 offset, Uint8 R, Uint8 G, Uint8 B);
void Slock(SDL_Surface *screen);
void Sulock(SDL_Surface *screen);

};
