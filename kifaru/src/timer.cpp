#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "config.h"
#include "timer.h"

#define TICK_INTERVAL    10                 //100Hz counter

using namespace std;

namespace ephidrena
{

Timer::Timer()
{
 
}


Timer::~Timer()
{
    SDL_RemoveTimer(timer_id);
}

void Timer::Install()
{
   timer_id = SDL_AddTimer(TICK_INTERVAL, PushSequencerEvent, this);
    
    if (timer_id==NULL)
    {
        cout << ("Timern funker ikke!") << endl;
    }        
}

Uint32 Timer::PushSequencerEvent(Uint32 interval, void* param)
{
    static SDL_Event event_sequencer;
    
    event_sequencer.type = SDL_USEREVENT;
    SDL_PushEvent(&event_sequencer);
    return interval;
}


Uint32 Timer::Benchmark()
{
    static Uint32 next_time = 0;
    Uint32 now;

    now = SDL_GetTicks();
    if ( next_time < now ) 
    {
        next_time = now + TICK_INTERVAL;
        return(0);
    }
    return(next_time-now);
}

};

