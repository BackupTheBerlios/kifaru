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
	speed		= 3;
	weight		= 1;
	magnetism	= 0;
	distance	= 200;
	k		= 100;
	trajectoryPos	= NULL;
	
	xPos = rand() %  799;
	yPos = rand() %  599;
	zPos = rand() %  2047;

}

Particle::~Particle()
{
}

void Particle::Run(Uint32 max)
{
	if(yPos < screen->h )
		yPos += speed;
	else
		yPos  = 0;
	
	if(zPos < max )
		zPos += speed;
	else
		zPos  = 0;
}

Stream::Stream()
    : Effect("Stream")
{
	this->preScaleCount = 256;
	this->particleCount = 50;
	this->zMax	    = 1023;
	
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

	std::cout << "preScaleCount er: " << preScaleCount << std::endl;
	std::cout << "zMax er: " << zMax << std::endl;
	
	while(scaleIt < preScaleCount)
	{
	    tempSurface = sge_CreateAlphaSurface(SDL_SWSURFACE, 
			    			scaleIt+1, scaleIt+1); 

	    scale =  float(scaleIt) / preScaleCount;	
	   
//	    std::cout << "scale: " << scale << "    scaleIt: " << scaleIt << std::endl;
	    
	    sge_transform(pic, tempSurface, 0, scale, scale, 0, 0, 0, 0, 0);

	    scaledParticles[scaleIt] = tempSurface;
	    scaleIt++;
	}

	SDL_FreeSurface(pic);

//	std::cout << std::endl << "Skalerte " << scaleIt-1 << " baller" << std::endl;

}

void Stream::Render(SDL_Surface* screen)
{
	//std::cout << "Planer om å rendre litt da..." << std::endl;
	static Uint32 count = 0;
	Uint32	pCnt = 0;
	Sint16  X,Y,Z;

	
	SDL_FillRect(screen,NULL,0);
	Particle* particle;
	
	while(pCnt < particleCount)
	{
		particle = particles[pCnt];
		X  = (particle->xPos * 2250) / (particle->zPos + 1200);
		Y  = (particle->yPos * 2250) / (particle->zPos + 1200);
		Z  = (particle->zPos / 16);

		sge_BlitTransparent(scaledParticles[Z], screen, 0,0, X,Y, 
							  Z,Z, 0,32);
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
