#include <iostream>
#include <SDL/SDL.h>
#include <SDL/sge.h>
#include <cstdlib>
#include "effect.h"
#include "config.h"
#include "ParticleStream.h"
#include "ImageProcessing.h"


namespace ephidrena {

	extern SDL_Surface *screen;


	Particle::Particle()
{
	alpha 		= 255;
	gamma 		= 127;
	colorkey	= 0;
	xspeed		= 3+(rand() %5);
	yspeed		= 3+(rand() %5);
	zspeed		= 3+(rand() %5);
	xdir		= (rand() %1);
	ydir		= (rand() %1);
	zdir		= (rand() %1);
	lifeSpan	= 250+(rand() %250);
	weight		= 1;
	magnetism	= 0;
	distance	= 200;
	k		= 100;
	trajectoryPos	= NULL;
	
	xPos = rand() %  screen->w*2;
	yPos = rand() %  screen->h*2;
	zPos = rand() %  2048;
}

Particle::~Particle()
{
}


void Particle::Resurrect()
{
	xspeed		= 3+(rand() %5);
	yspeed		= 3+(rand() %5);
	zspeed		= 3+(rand() %5);
	xdir		= (rand() %1);
	ydir		= (rand() %1);
	zdir		= (rand() %1);
	lifeSpan	= 250+(rand() %250);

}

void Particle::Run(Uint32 max)
{

	lifeSpan--;
	if(!lifeSpan)
		this->Resurrect();
	
	
	xdir = (xPos > screen->w) || (xPos < 0) ? !xdir : xdir;
	xPos = xdir ? xPos - xspeed : xPos + xspeed;

/*	yPos-=1;
	if(yPos<0)
		yPos = screen->h;
*/	
	ydir = (yPos > screen->h) || (yPos < 0) ? !ydir : ydir;
	yPos = ydir ? (yPos - yspeed) : (yPos + yspeed);

	//zPos++;
	zdir = (zPos > (max-zspeed)) || (zPos < zspeed) ? !zdir : zdir;
	zPos = zdir ? (zPos - zspeed) : (zPos + zspeed);
	
		
	
}

Stream::Stream()
    : Effect("Stream")
{
	this->preScaleCount = 128;
	this->particleCount = 127;
	this->zMax	    = 2048;
	
}

Stream::~Stream()
{
	//delete[] particles;
}
	
void Stream::preScaleParticle(SDL_Surface* pic)
{
	Uint32		scaleIt = 0;
	float		scale = 1.0;
	SDL_Surface*	tempSurface;

	//std::cout << "preScaleCount er: " << preScaleCount << std::endl;
	//std::cout << "zMax er: " << zMax << std::endl;
	
	while(scaleIt < preScaleCount)
	{
	    tempSurface = sge_CreateAlphaSurface(SDL_HWSURFACE, 
			    			scaleIt+1, scaleIt+1); 

	    scale =  float(scaleIt/2) / preScaleCount;	
	   
//	    std::cout << "scale: " << scale << "    scaleIt: " << scaleIt << std::endl;
	    
	    sge_transform(pic, tempSurface, 0, scale, scale, 0, 0, 0, 0, SGE_TAA);

	    scaledParticles[scaleIt] = tempSurface;
	    scaleIt++;
	}

	SDL_FreeSurface(pic);

//	std::cout << std::endl << "Skalerte " << scaleIt-1 << " baller" << std::endl;

}

void Stream::Render(SDL_Surface* screen)
{
	static Uint32 count = 0;
	Uint32	pCnt = 0;
	Sint16  X,Y,Z;
	
	SDL_FillRect(screen,NULL,0);
	Particle* particle;
	
	while(pCnt < particleCount)
	{
		particle = particles[pCnt];
		X  = ((particle->xPos) * 750) / (particle->zPos + 460);
		Y  = ((particle->yPos) * 790) / (particle->zPos + 460);
		Z  = (particle->zPos/32);

	//	X += (screen->w/2);
	//	Y += (screen->h/2);
		sge_BlitTransparent(scaledParticles[Z], screen, 0,0, X,Y, 
							  Z,Z, 0,8);
		particle->Run(zMax);
		pCnt++; 
	}
}

void Stream::Init(AttrMap)
{
	SDL_Surface* pic;
    	SDL_RWops *rwop;
	Uint32 pCnt = 0;
    	
	rwop = SDL_RWFromFile("gfx/alphapartikkel1.png", "rb");
    	pic = SDL_ConvertSurface(IMG_LoadPNG_RW(rwop), screen->format, SDL_SWSURFACE);
	
	if(pic)
		this->preScaleParticle(pic);
	else
	{	std::cout << "No alpha particle texture loaded!" << std::endl;
		return;
	}
	//SDL_FreeSurface(pic);

	while(pCnt < preScaleCount)
	{
		particles[pCnt] = new Particle();
		Particle::Particle();
		pCnt++;
	}
		
	//std::cout << "Ferdig med Stream init!" << std::endl
//		<< "Lagde " << pCnt << " partikler. " << std::endl;
	return;
}

};
