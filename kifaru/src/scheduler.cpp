#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "config.h"
#include "scheduler.h"
#include "effect.h"
#include "inits.h"

using namespace std;

namespace ephidrena
{



Scheduler::Scheduler()
{
    
}

Scheduler::~Scheduler()
{
    
}

void Scheduler::EventHandler()
{
    Uint32 EffectCount=0,EffectCurrent=0,Demo_Exit=0;
    SDL_Event event;
    
    FXList fxlist;
    Effect *effect,*effect2;
    
	cout << "schedulern" << endl;

    effect = new Image;
    effect->fileName="gfx/alphapartikkel1.png";
    effect->LoadPNG();
    	cout << "lasta png" << endl; 
    cout  << effect->fileName << endl;
    effect->xofs=0;
    effect->yofs=24;

    effect2 = new Jall;

    while (Demo_Exit==0)
    {
        effect->Render(screen);    
        SDL_Flip(screen);
        while ( SDL_PollEvent(&event) )
        {
                if (event.type == SDL_USEREVENT) EffectCount=fxlist.CheckTime();
                if (event.type == SDL_QUIT ) Demo_Exit = 1;
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE ) Demo_Exit = 1;
                    if (event.key.keysym.sym == SDLK_SPACE  ) Demo_Exit = 1;
                }    
        }    

        if ( EffectCount > EffectCurrent)
        {
            effect = effect2;
        }    
         SDL_Delay(50);   
    }   
    delete effect;
    delete effect2;
   
}    


FXList::FXList()
{
    
}

FXList::~FXList()
{
    
}

Uint32 FXList::CheckTime()
{
    static Uint32 FrameCount=0,FrameNext=705,EffectCount=0;
    
    FrameCount++;
    if (FrameCount > FrameNext) EffectCount++;
    
    //cout << "timecheck!" << endl;
    return EffectCount;
}



};
