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
#include "SDL_rotozoom.h"

using namespace std;

namespace ephidrena{


Image::Image()
    : Effect("Image")
{
    this->xofs		= 0;
    this->yofs		= 0;
    this->scale		= 1.0;
    this->xscale	= 1.0;
    this->yscale	= 1.0;
    this->rotate	= 0;
    this->alpha		= 255;
}

Image::~Image()
{
    
}    


void Image::Init(AttrMap attrmap)
{
    AttrMap::const_iterator it;
    
    cout << "mekker attrmap!" << std::endl;
    
    it = attrmap.find("filename");
    this->fileName = (char*)it->second.c_str();
    cout << "hei!" << std::endl;
    this->LoadPNG();
    
   
    cout << "hei!" << std::endl;
    it = attrmap.find("xofs");
    if (it != attrmap.end())
        this->xofs = str2int((char*)it->second.c_str());
    
    it = attrmap.find("yofs");    
    if(it != attrmap.end())
	this->yofs = str2int((char*)it->second.c_str());

    it = attrmap.find("scale");
    if(it !=attrmap.end())
	    this->scale = (str2int((char*)it->second.c_str()) /100.0 );

    it = attrmap.find("xscale");
    if(it !=attrmap.end())
	    this->xscale = (str2int((char*)it->second.c_str()) /100.0 );

    it = attrmap.find("yscale");
    if(it !=attrmap.end())
	    this->yscale = (str2int((char*)it->second.c_str()) /100.0 );

    it = attrmap.find("rotate");
    if(it !=attrmap.end())
	    this->rotate = str2int((char*)it->second.c_str());

    it = attrmap.find("alpha");
    if(it !=attrmap.end())
	    this->alpha = str2int((char*)it->second.c_str());

    cout << "mekka attrmap!" << std::endl;
	    
}


void Image::Render (SDL_Surface *screen)
{
	SDL_Surface *workScreen = this->pic;

	Uint32 smooth = 1;
	
        SDL_Rect dest;
        dest.x = this->xofs;
        dest.y = this->yofs;

	if (rotate)
	{
		workScreen = rotozoomSurface (this->pic, 
				rotate, scale, smooth); 
	}
	else if(scale || xscale || yscale)
	{
		workScreen =  zoomSurface (this->pic, 
				this->scale * this->xscale, 
				this->scale * this->yscale, smooth);
	}

	SDL_SetAlpha(workScreen,SDL_SRCALPHA,5);	

        SDL_BlitSurface(workScreen, NULL, screen, &dest);
	SDL_FreeSurface(workScreen);
	
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
    this->pic = IMG_LoadPNG_RW(rwop);
    if (!this->pic) cout << "LoadPNG tryna!" << endl;
}


};
