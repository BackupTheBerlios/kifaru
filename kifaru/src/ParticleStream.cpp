#include <iostream>
#include <SDL/SDL.h>
#include <SDL/sge.h>
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
	speed		= 1;
	weight		= 1;
	magnetism	= 0;
	xPos		= 0;
	yPos		= 0;
	zPos		= 0;
	trajectoryPos	= NULL;

}

Particle::~Particle()
{
	
}


Stream::Stream()
    : Effect("Stream")
{

}

Stream::~Stream()
{
}
	
void Stream::preScaleParticle(SDL_Surface* pic)
{
	Uint32		 scaleIt = 0;
	const Uint32	 scales  = 256;
	float		 scale = 1;
	SDL_Surface*	 tempSurface;
	SDL_Surface*	 tempSurface2;
    	SDL_PixelFormat* fmt = screen->format;
	
	while(scaleIt < scales)
	{
		//std::cout << "Mekker skalert partikkel nr. " << scaleIt << std::endl;
		
		tempSurface = sge_copy_surface(pic);
		tempSurface2 = SDL_CreateRGBSurface(SDL_SWSURFACE, 
							256, 256, 
							32, 
							fmt->Rmask, fmt->Gmask, 
							fmt->Bmask, fmt->Amask);
		scale = (float) (scaleIt + 1) / scales ;	
		sge_transform( tempSurface, tempSurface2, 0, 
					scale, scale,
					0, 0,
					0, 0,
					0);

		
		scaledParticles[scaleIt] = tempSurface2;
		scaleIt++;
	}

	std::cout << "Ferdig med loopen!" << std::endl;

	return;
	
}

void Stream::Render(SDL_Surface* _screen)
{
	static Uint32 count = 0;
	
	if (count > 255)
		count = 0;
	
	std::cout << "Klar for å rendre partikkel " << count << std::endl;
	
	sge_Blit(scaledParticles[count], screen, 0,0, 10,10, 
				256, 256);
				//colorKey,255);
	count++;
}

void Stream::Init(AttrMap)
{
	SDL_Surface* pic;
    	SDL_RWops *rwop;
    	rwop = SDL_RWFromFile("gfx/alphapartikkel1.png", "rb");
    	pic = IMG_LoadPNG_RW(rwop);
	if(pic)
	std::cout << "Vi har png!" << std::endl;
	this->preScaleParticle(pic);
	SDL_FreeSurface(pic);
	std::cout << "Ferdig med Stream init!" << std::endl;
	return;
}

};
