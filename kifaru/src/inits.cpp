#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "primitives.h"
#include "config.h"
#include "inits.h"

using namespace std;

namespace ephidrena
{

SDL_Surface *screen;
SDL_Surface *pic1;
SDL_Surface *pic2;

extern SDL_Surface *screen;


Init::Init()
{
    
}

Init::~Init()
{
    
}    


void Init::SDL()
{

 if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) <0)
  {
      cout << ("Detta suger! Fåkke opp SDL. Feilkode: %s", SDL_GetError()) << endl;
      return;
  }   
  
//  SDL_ShowCursor(0);   
  
  atexit(SDL_Quit);
  
  screen = SDL_SetVideoMode(1280,1024, 32, 
                    SDL_SWSURFACE|SDL_HWPALETTE|SDL_DOUBLEBUF);
  if (screen==NULL)
  {
      cout << ("Fåkke satt videomode %s",SDL_GetError()) << endl;
      return;
  }
  
  cout << ("Kliner til!") << endl;    
  return;
}

};

