#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "config.h"
#include "primitives.h"
#include "inits.h"
#include "EffectFactory.h"
#include "tools.h"
#include "effect.h"
#include "ImageProcessing.h"
//#include "SDL_rotozoom.h"

using namespace std;

namespace ephidrena{


Image::Image()
	: Effect("Image")
{
	SDL_PixelFormat* fmt = screen->format;
	int w   = screen->w;
	int h   = screen->h;
	
	this->xofs = 0;
	this->yofs = 0;
	this->scale = 1.0;
	this->xscale = 1.0;
	this->yscale = 1.0;
	this->rotate = 0.0;
	this->alpha = 255;
	this->hasAlpha = false;
    
	this->pic = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
		fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask); 
	this->workScreen = this->pic;
    
	this->tfScreen	= SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 
		fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask); 
}

Image::~Image()
{
	SDL_FreeSurface(this->pic);
	SDL_FreeSurface(this->tfScreen);
}    


bool Image::Init(AttrMap attrmap)
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
	{
		this->alpha = str2int(it->second.c_str());
		this->hasAlpha = true;
	}
    
	return true;
}


void Image::Render (SDL_Surface *screen)
{
	const Uint32 clear = 0x000000;
	
	SDL_Rect dest;
	dest.x = xofs;
	dest.y = yofs;

	if(scale || xscale || yscale || rotate)
	{
		sge_transform( pic, tfScreen, rotate, 
				scale*xscale, scale*yscale,
				pic->w/2, pic->h/2,
				screen->w/2,screen->h/2,
				0);
		
		workScreen = tfScreen;
	}

	if(hasAlpha)
		sge_BlitTransparent(workScreen, screen, 0,0, 0,0, 
				screen->w, screen->h,
				clear,alpha);
	else
		SDL_BlitSurface(workScreen, NULL, screen, &dest);

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
	pic = sge_copy_surface(IMG_LoadPNG_RW(rwop));
	if (!pic) 
		cout << "LoadPNG tryna!" << endl;
}


};
