#include <iostream>
#include <cstdlib>
#include <math.h>
#include "effect.h"
#include "config.h"
#include "ParticleStream.h"
#include "ImageProcessing.h"
#include "tools.h"


namespace ephidrena {

	extern SDL_Surface *screen;

Particle::Particle()
{
	
	alpha 		= 255;
	gamma 		= 127;
	colorkey	= 0;
	
	xspeed		= Rnd(2,7);
	yspeed		= Rnd(2,7);
	zspeed		= Rnd(2,7);
	xdir		= Rnd(0,1);
	ydir		= Rnd(0,1);
	zdir		= Rnd(0,1);
	lifeSpan	= Rnd(5,100);
	weight		= Rnd(5,100);
	magnetism	= Rnd(10,50);
	
	trajectoryPos	= NULL;
	
	xPos = Rnd(0, (screen->w/4)) - (screen->w/4);
	yPos = Rnd(0, (screen->h/4)) - (screen->h/4);
	zPos = Rnd(0,  ZMAX);

}

Particle::~Particle()
{
}


void Particle::Resurrect()
{
	xspeed		= Rnd(1,5);
	yspeed		= Rnd(1,5);
	zspeed		= Rnd(1,6);
	xdir		= Rnd(0,1);
	ydir		= Rnd(0,1);
	zdir		= Rnd(0,1);
	lifeSpan	= Rnd(50,250);
	if(yPos > (screen->h/2)-20)
		yPos = Rnd(0,100);
}

void Particle::Run()
{
	static Sint32 wMin = -(screen->w/2);
	static Sint32 wMax = screen->w/2;
	static Sint32 hMin = -(screen->h/2);
	static Sint32 hMax = screen->h/8;

	lifeSpan--;
	if(!lifeSpan)
		this->Resurrect();

	this->ZField(&zPos, ZMAX, zspeed/6);
	this->Move(&xdir, &xPos, wMin, wMax, xspeed/6);
	this->Move(&ydir, &yPos, hMin, hMax, yspeed/2);
	//this->Move(&zdir, &zPos, 1, ZMAX-1 , zspeed);
//
 	//this->GravityPull(&ydir, &yPos, yspeed);	
/*	
	xPos+=screen->w/2;	
	this->ZField(&xPos, screen->w, xspeed/3);
	xPos-=screen->w/2;
*/
}

void Particle::Move(bool* dir, int* pos, Sint32 min, Sint32 max, int speed)
{
	*dir = (*pos >= max) || (*pos <=  min) ? !(*dir) : *dir;
	*pos = *dir ? *pos - speed : *pos + speed;
}


void Particle::ZField(Sint32* pos, int max, int speed)
{
	(*pos)-=speed+1;
	*pos = *pos < 0 ? max : *pos;
}

void Particle::GravityPull(bool* dir, int* pos, int speed)
{
	static int bottom = screen->h/2;

	if (*pos == bottom-20 || *pos < 0)
		return;			//dead ball or not within range
	
	*pos += (*pos + (screen->h )) / (screen->h); // <-too fake!
	
}
	
Stream::Stream()
    : Effect("Stream")
{
	this->preScaleCount = ZSCALES;
	this->particleCount = PARTICLES;
	this->distance	    = 200;
	this->k		    = 100;
	this->alpha	    = 255;	
}

Stream::~Stream()
{
	delete[] particles;
}
	

void Stream::Render(SDL_Surface* screen)
{
	static Uint32 count = 0;
	Uint32	pCnt = 0;
	Sint32	scale;
	Sint16  X,Y,Z;
	Uint32	size;
	Uint32* sortedParticles[ZMAX];
	Uint32	tmp1, tmp2;
	SDL_Rect* dst;
	Particle* particle;
	
	//SDL_FillRect(screen,NULL,0);


	SDL_Surface* display=SDL_GetVideoSurface();

	
	// convert the temporary surface to display format
	static SDL_Surface* back=SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 
		display->format->BitsPerPixel, 
		display->format->Rmask,
		display->format->Gmask,
		display->format->Bmask,
		display->format->Amask);

	SDL_BlitSurface(backdrop,0,back,0);	

	// create blending surface
	SDL_Surface* blend = sge_copy_surface(back);
	
	while(pCnt < particleCount)
	{
		particle= particles[pCnt];
		particle->Run();
		
		X = Sint16(500.0 * particle->xPos / (-1.0 + particle->zPos));
		Y = Sint16(100.0 * particle->yPos / (1.0 - particle->zPos));
		Z = Sint16(( particle->zPos ) / (ZMAX / ZSCALES) );
		Z = Z > ZSCALES-1 ? ZSCALES-1 : Z;

		X += (screen->w);
		//Y += (screen->h);
		size = scaledSize[Z];
		
		sge_Blit(scaledParticles[Z], blend, 0,0, X,Y, 
							  size,size);
		pCnt++; 
	}
	
	sge_Blit(blend,display,0,0,0,0,blend->w,blend->h);
	SDL_FreeSurface(blend);

}

bool Stream::Init(AttrMap)
{
	SDL_Surface* pTexture;
	SDL_RWops *rwop;
	Uint32 pCnt = 0;

	if(rwop = SDL_RWFromFile("data/alphapartikkel1.png", "rb"))
		pTexture = SDL_DisplayFormatAlpha(IMG_LoadPNG_RW(rwop)); 
    	else
		return false;

	if(rwop = SDL_RWFromFile("data/solisplanum2.png", "rb"))
		backdrop = IMG_LoadPNG_RW(rwop);
    	else 
		return false;
    
	this->preScaleParticle(pTexture);
    
	SDL_FreeSurface(pTexture);
	
	while(pCnt < particleCount)
	{
		particles[pCnt] = new Particle();
		pCnt++;
	}
	
	return true;
}

void Stream::preScaleParticle(SDL_Surface* pic)
{
	Uint32 scaleIt = ZSCALES;
	Uint32 cnt = 0;
	float scale = 1.0;
	SDL_Surface* tempSurface;

	while(scaleIt)
	{
		tempSurface = sge_CreateAlphaSurface(SDL_SWSURFACE, 
				scaleIt, scaleIt); 

		scale = (float)(scaleIt / 8) / ZSCALES;
		sge_transform(pic, tempSurface, 0,
				scale , scale , 
				0, 0, 0, 0, 
				SGE_TAA | SGE_TSAFE);

		shadeSurface(tempSurface, ZSCALES - scaleIt);

		if(scaleIt < 48)
			blurSurface(tempSurface,5);
		if(scaleIt > 64)
			blurSurface(tempSurface,scaleIt);

		scaledParticles[cnt] = tempSurface;
		scaledSize[cnt] = scaleIt;
		scaleIt--;
		cnt++;
	}
}

void Stream::blurSurface(SDL_Surface* pic, int amount)
{
	SDL_PixelFormat *fmt;
	Uint32 rVal, gVal, bVal, aVal;
	Sint32 xl,yl;
	Uint32 ld = pic->w;
	Uint32 lu = -(ld);
	Uint8 r,g,b;
	Uint8 r1,g1,b1;
	Uint8 r2,g2,b2;
	Uint8 r3,g3,b3;
	Uint8 r4,g4,b4;
	Uint8 a,a1,a2,a3,a4;
	Uint32 *pixels;
	Uint32 *pixel;
	Uint32 cnt;

	pixels = (Uint32*)pic->pixels;		
	if(pixels == NULL)
		return;
		
	
	fmt = screen->format;

	while(cnt < amount)
	{
		for(yl=1; yl < pic->h-2; yl++)
		{
			for(xl =1; xl < pic->w-2; xl++)
			{
				pixel = pixels + xl + (yl*pic->w);
				SDL_GetRGBA(*pixel,      fmt, &r,  &g,  &b,  &a);
				SDL_GetRGBA(pixel[-1],   fmt, &r1, &g1, &b1, &a1);
				SDL_GetRGBA(pixel[ 1],   fmt, &r2, &g2, &b2, &a2);
				SDL_GetRGBA(pixel[ld],   fmt, &r3, &g3, &b3, &a3);
				SDL_GetRGBA(pixel[lu],	 fmt, &r4, &g4, &b4, &a4);

				rVal = Uint32((r + r1 + r2 + r3 + r4) / 5.0);
				gVal = Uint32((g + g1 + g2 + g3 + g4) / 5.0);
				bVal = Uint32((b + b1 + b2 + b3 + b4) / 5.0);
				aVal = Uint32((a + a1 + a2 + a3 + a4) / 5.0); 

				r = (Uint8) (rVal < 255 ? rVal : 255);
				g = (Uint8) (gVal < 255 ? gVal : 255);
				b = (Uint8) (bVal < 255 ? bVal : 255);
				a = (Uint8) (aVal < 255 ? aVal : 255);
		
				*pixel = a && (r+g+b) ? SDL_MapRGBA(fmt, r, g, b, a) : 0;
			}
		}
		cnt++;
	}		
}

void Stream::shadeSurface(SDL_Surface* pic, int amount)
{
	SDL_PixelFormat *fmt;
	Sint32 xl,yl;
	Uint8 r,g,b,a;
	Uint32* pixels;
	Uint32* pixel;
	Uint32 cnt;

	pixels = (Uint32*)pic->pixels;		
	if(!pixels)
		return;

	amount *=4;
	
	fmt = screen->format;

	for(yl=0; yl < pic->h-1; yl++)
	{
		for(xl =0; xl < pic->w-1; xl++)
		{
			pixel = pixels + xl + (yl*pic->w);
			SDL_GetRGBA(*pixel, pic->format, &r,  &g,  &b,  &a);
			r = r - amount > 0 ? r - amount : 0;
			g = g - amount > 0 ? g - amount : 0; 
			b = b - amount > 0 ? b - amount : 0;
	/*hack*/	a = ((r + g + b ) / 3 )- amount > 0 ? ((r + g + b )) / 3 - amount : 0; 
			*pixel = a ? SDL_MapRGBA(pic->format, r, g, b, a) : 0;
		}	
		cnt++;;
	}
	
}			

};
