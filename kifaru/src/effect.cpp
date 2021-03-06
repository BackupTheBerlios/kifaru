#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "config.h"
#include "primitives.h"
#include "inits.h"
#include "EffectFactory.h"
#include "tools.h"
#include "effect.h"
#include "ImageProcessing.h"
#include "ParticleStream.h"

using namespace std;

namespace ephidrena
{

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
        	if (SDL_LockSurface(screen) < 0) 
			return;
    	}
}
            
void Effect::SULock(SDL_Surface *screen)
{
	if ( SDL_MUSTLOCK(screen) ) 
		SDL_UnlockSurface(screen);
}


void Effect::ClearScreen(SDL_Surface *screen)
{
	/* Set the screen to black */
	if ( SDL_LockSurface(screen) == 0 ) 
	{
		Uint32 color;
		Uint8 *pixels;
		color = SDL_MapRGB(screen->format, 64, 64, 64);
		pixels = (Uint8 *)screen->pixels;
                
		for ( int i=0; i<screen->h; ++i )
		{
			memset(pixels, color,
			screen->w*screen->format->BytesPerPixel);
			pixels += screen->pitch;
		}
		SDL_UnlockSurface(screen);
	}
}


Jall::Jall()
	: Effect("Jall")
{

}

Jall::~Jall()
{

}


bool Jall::Init(AttrMap attrmap)
{
     
	return true;
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
		if (YSin > 1)
			YSin = -1;
		ys = Uint8(sin (YSin)  );
		vri++;
		vreng+=0.7;
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


bool Jull::Init(AttrMap attrmap)
{
	return true;
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
		if (YSin > 1)
			YSin = -1;
		ys = Uint8(sin (YSin)  );
		vri++;
		vreng+=0.7;
		XSin+=0.13;
		YSin+=0.15;
	}        
    
	SULock(screen);
}    

REGISTER_EFFECT(Image);
REGISTER_EFFECT(Jall);
REGISTER_EFFECT(Jull);
REGISTER_EFFECT(Stream);
};
