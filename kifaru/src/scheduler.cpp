#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "config.h"
#include "scheduler.h"
#include "effect.h"
#include "inits.h"
//#include "tools.h"
//#include "tools.cpp"

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
    SDL_Event event;
    Uint32 total_ticks;

    std::cerr << "N� vil vi ha events!" << std::endl;

    
    root_effect->prepare();

    while (!root_effect->isDone(total_ticks)  ) {

	root_effect->Render(screen);
	SDL_Flip(screen);

	while (SDL_PollEvent(&event)) {
	    if (event.type == SDL_USEREVENT) {
		//cout <<("%i\n",total_ticks);
		total_ticks++;
		root_effect->newTick(total_ticks);
	    }
	    if (event.type == SDL_QUIT )
		goto out;
	    if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE
		    || event.key.keysym.sym == SDLK_SPACE)
		    goto out;
	    }
        }
	
	SDL_Delay(50);
    }

out:
    return;
};   

};
