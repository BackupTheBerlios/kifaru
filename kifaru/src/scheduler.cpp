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
    EffectList::iterator ei;
    Effect *effect;
    SDL_Event event;
    Uint32 effect_ticks = 0, total_ticks = 0;

    ei = effects.begin();

    while (ei != effects.end()) {
	effect = *ei;

	effect->Render(screen);
	SDL_Flip(screen);

	while (SDL_PollEvent(&event)) {
	    if (event.type == SDL_USEREVENT) {
		effect_ticks++;
		total_ticks++;
		if (effect->done(effect_ticks)) {
		    effect_ticks = 0;
		    ++ei;
		}
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
}    

};
