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
    this->scale		= 1;
    this->xscale	= 1;
    this->yscale	= 1;
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
	    this->rotate = (str2int((char*)it->second.c_str()));
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

SDL_Surface* Image::Scale(SDL_Surface *original, float xscale, float yscale)
{
    Uint32 xofs = 0, yofs = 0, dofs = 0;
    float  sofs = 0, sinc = 1 / xscale, sy = 0;
    Uint32 *pixels;
    SDL_Surface *scaled = SDL_CreateRGBSurface(SDL_SWSURFACE,
          (xscale * original->w), (yscale * original->h), original->format->BitsPerPixel,
          original->format->Rmask, original->format->Gmask , original->format->Bmask, original->format->Amask);

     Uint32 *original_pixels = static_cast<Uint32 *>(original->pixels);
     Uint32 *scaled_pixels   = static_cast<Uint32 *>(scaled->pixels);

     while(yofs < (yscale * original->h))
     {
        while(xofs < (xscale * original->w))
        {
            scaled_pixels[dofs] = original_pixels[(Uint32)sofs];
            dofs++;
            sofs += sinc;
        }

        sy += 1 / yscale;
        sofs = sy * original->pitch;
      }

}



void Image::RotatePicture (SDL_Surface *screen, SDL_Surface *picture, int rotate, int smooth) 
{
	SDL_Surface *rotozoom_picture;
	SDL_Rect dest;
	static int framecount = 360, framemax = 4*360, frameinc=1;
	static float zoomf;

	/* Rotate and display the picture */
	SDL_Surface *pictureX, *picture_again;
	char *bmpfile;


	framecount += frameinc;

        if ((framecount % 360)==0) 
	    frameinc++;
       
//        ClearScreen(screen);
	zoomf=(float)framecount/(float)framemax;
	zoomf=1.5*zoomf*zoomf;
	if ((rotozoom_picture=rotozoomSurface (picture, framecount*rotate, zoomf, smooth))!=NULL) 
	{
	    dest.x = (screen->w - rotozoom_picture->w)/2;;
	    dest.y = (screen->h - rotozoom_picture->h)/2;
	    dest.w = rotozoom_picture->w;
	    dest.h = rotozoom_picture->h;
	    SDL_BlitSurface(rotozoom_picture, NULL, screen, &dest);
	}
				
 		/* Final display with angle=0 */
			
		if ((rotozoom_picture=rotozoomSurface (picture, 0.01, zoomf, smooth))!=NULL) 
		{
			dest.x = (screen->w - rotozoom_picture->w)/2;;
			dest.y = (screen->h - rotozoom_picture->h)/2;
			dest.w = rotozoom_picture->w;
			dest.h = rotozoom_picture->h;
  			SDL_BlitSurface(rotozoom_picture, NULL, screen, &dest);
		}		
		
}

void Image::ZoomPicture (SDL_Surface *workScreen, SDL_Surface *picture, int smooth, float zoomxf, float zoomyf) 
{

	workScreen =  zoomSurface (picture, zoomxf, zoomyf, smooth);
}



};
