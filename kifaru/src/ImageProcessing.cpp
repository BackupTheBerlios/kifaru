#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/sge.h>
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
    this->rotate	= 0.0;
    this->alpha		= 128;
    this->tfScreen	= SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 32, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask); 
    this->workScreen	= SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 32, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask); 
    this->pic		= SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 32, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask); 
}

Image::~Image()
{
    
}    


void Image::Init(AttrMap attrmap)
{
    AttrMap::const_iterator it;
    
    it = attrmap.find("filename");
    this->fileName = (char*)it->second.c_str();
    this->LoadPNG();
   
    it = attrmap.find("xofs");
    if (it != attrmap.end())
        this->xofs = str2int(it->second.c_str());
    
    it = attrmap.find("yofs");    
    if(it != attrmap.end())
	this->yofs = str2int(it->second.c_str());

    it = attrmap.find("scale");
    if(it !=attrmap.end())
	    this->scale = str2int(it->second.c_str()) /100.0 ;

    it = attrmap.find("xscale");
    if(it !=attrmap.end())
	    this->xscale = str2int(it->second.c_str()) /100.0 ;

    it = attrmap.find("yscale");
    if(it !=attrmap.end())
	    this->yscale = str2int(it->second.c_str()) /100.0 ;

    it = attrmap.find("rotate");
    if(it !=attrmap.end())
	    this->rotate = str2float(it->second.c_str()) ;

    it = attrmap.find("alpha");
    if(it !=attrmap.end())
	    this->alpha = str2int(it->second.c_str());
}


void Image::Render (SDL_Surface *screen)
{
	Uint32 clear = 0x000000;
	
        SDL_Rect dest;
        dest.x = this->xofs;
        dest.y = this->yofs;

	if(scale || xscale || yscale || rotate)
	{
		sge_transform( this->pic, tfScreen, this->rotate, 
					this->scale*this->xscale, this->scale*this->yscale,
					-1*this->xofs, -1*this->yofs,
					0,0,
					0);
	}

  //      SDL_BlitSurface(workScreen, NULL, screen, &dest);

	sge_BlitTransparent(this->tfScreen, screen, 0,0, 0,0, 
				screen->w, screen->h,
				clear,9);
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
    this->pic = sge_copy_surface(IMG_LoadPNG_RW(rwop));
    if (!this->pic) cout << "LoadPNG tryna!" << endl;
}


};
