#include <iostream>
#include <cstdlib>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/sge.h>
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
	lifeSpan	= Rnd(50,250);
	weight		= Rnd(50,100);
	magnetism	= Rnd(10,50);
	
	trajectoryPos	= NULL;
	
	xPos = Rnd(0, screen->w);
	xPos -= (screen->w/2);
	
	yPos = Rnd(0, screen->h);
	yPos -= (screen->h/2);
	
	zPos = Rnd(0,  ZMAX);
}

Particle::~Particle()
{
}


void Particle::Resurrect()
{
	xspeed		= Rnd(1,5);
	yspeed		= Rnd(1,5);
	zspeed		= Rnd(3,7);
	xdir		= Rnd(0,1);
	ydir		= Rnd(0,1);
	zdir		= Rnd(0,1);
	lifeSpan	= Rnd(50,250);
}

void Particle::Run()
{
	static Sint32 wMax = screen->w/2;
	static Sint32 hMax = screen->w/2;
	static Sint32 wMin = -(screen->w/2);
	static Sint32 hMin = -(screen->h/2);

	lifeSpan--;
	if(!lifeSpan)
		this->Resurrect();

//	xdir = (xPos > wMax) || (xPos < wMin) ? !xdir : xdir;
//	xPos = xdir ? xPos - xspeed : xPos + xspeed;

	this->Move(&xdir, &xPos, wMin, wMax, xspeed);
	this->Move(&ydir, &yPos, hMin, hMax, yspeed);
	
	this->Move(&zdir, &zPos, 1, ZMAX-1 , zspeed);

// 	this->GravityPull(&ydir, &yPos, yspeed);	
	
//	this->ZField(&zPos, ZMAX, zspeed);
	
}

void Particle::Move(bool* dir, signed int* pos, int min, int max, int speed)
{
	*dir = (*pos >= max) || (*pos <=  min) ? !(*dir) : *dir;
	*pos = *dir ? *pos - speed : *pos + speed;
}


void Particle::ZField(int* pos, int max, int speed)
{
	int Pos = *pos;
	Pos+= speed;
	Pos = Pos > max ? 0 : Pos;
	*pos = Pos;
}


void Particle::GravityPull(bool* dir, int* pos, int speed)
{
	static int bottom = screen->h/2;

	if (*pos == bottom)
		return;			//dead ball
	
	*pos += *pos;
	
}
	
Stream::Stream()
    : Effect("Stream")
{
	this->preScaleCount = ZSCALES;
	this->particleCount = PARTICLES;
	this->distance	    = 550;
	this->k		    = 170;
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
	
	SDL_FillRect(screen,NULL,0);
	Particle* particle;
	
	while(pCnt < particleCount)
	{
		particle= particles[pCnt];
		//scale = particle->zPos / 100;
		//X  = (particle->xPos * distance) / (particle->zPos + distance);
		//Y  = (particle->yPos * distance) / (particle->zPos + distance);
		X = particle->xPos / 1+ (particle->zPos / distance);
		Y = particle->yPos / 1+ (particle->zPos / distance);
		Z  = particle->zPos / (ZMAX / ZSCALES) ;

		Z  = Z > ZSCALES-1 ? ZSCALES-1 : Z;

		X += (screen->w/2);
		Y += (screen->h/2);
	
		sge_BlitTransparent(scaledParticles[Z], screen, 0,0, X,Y, 
							  Z,Z, 0,alpha);
		particle->Run();
		pCnt++; 
	}
}

void Stream::Init(AttrMap)
{
	SDL_Surface* pic;
    	SDL_RWops *rwop;
	Uint32 pCnt = 0;
    	
	rwop = SDL_RWFromFile("gfx/alphapartikkel1.png", "rb");
    	pic = SDL_ConvertSurface(IMG_LoadPNG_RW(rwop), screen->format, 
					SDL_SWSURFACE);
	
	
	
	if(pic)
		this->preScaleParticle(pic);
	else
	{	std::cout << "No alpha particle texture loaded!" << std::endl;
		return;
	}
	SDL_FreeSurface(pic);

	while(pCnt < particleCount)
	{
		particles[pCnt] = new Particle();
		Particle::Particle();
		pCnt++;
	}
		
	return;
}

void Stream::preScaleParticle(SDL_Surface* pic)
{
	Uint32		scaleIt = 0;
	float		scale = 1.0;
	SDL_Surface*	tempSurface;

	while(scaleIt < ZSCALES)
	{
	    tempSurface = sge_CreateAlphaSurface(SDL_HWSURFACE, 
			    			scaleIt, scaleIt); 

	    scale = (float) (scaleIt/2) / ZSCALES;
	   
	    sge_transform(pic, tempSurface, 0, scale , scale , 0, 0, 0, 0, SGE_TAA);
	    if(scaleIt < 64 || scaleIt > 100)
	    	blurSurface(tempSurface,4);
	    scaledParticles[scaleIt] = tempSurface;
	    scaleIt++;
	}
}

void Stream::blurSurface(SDL_Surface* pic, int amount)
{
	SDL_PixelFormat *fmt;
	Uint32		rVal, gVal, bVal, aVal;
	Sint32		xl,yl;
	Uint32		ld = pic->w;
	Uint32		lu = -(ld);
	Uint8		r,g,b;
	Uint8		r1,g1,b1;
	Uint8		r2,g2,b2;
	Uint8		r3,g3,b3;
	Uint8		r4,g4,b4;
	Uint8		a,a1,a2,a3,a4;
	Uint32*		pixels;
	Uint32*		pixel;
	Uint32		cnt;

	SDL_LockSurface(pic);
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

			rVal = (r + r1 + r2 + r3 + r4) / 5.0;
			gVal = (g + g1 + g2 + g3 + g4) / 5.0;
			bVal = (b + b1 + b2 + b3 + b4) / 5.0;
			aVal = (a + a1 + a2 + a3 + a4) / 5.0; 

			rVal = rVal > 255 ? 255 : rVal;
			gVal = gVal > 255 ? 255 : gVal;
			bVal = bVal > 255 ? 255 : bVal;
			
			r = (Uint8) rVal;
			g = (Uint8) gVal;
			b = (Uint8) bVal;
			a = (Uint8) aVal;
		
			*pixel = a && (r+g+b) ? SDL_MapRGBA(fmt, r, g, b, 128) : 0;
		    }
	    }

	   cnt++;
	}
	
	SDL_UnlockSurface(pic);
			
}


};
