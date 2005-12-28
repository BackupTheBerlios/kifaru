#include <iostream>
#include "CompoundEffect.h"

namespace ephidrena
{

void CompoundEffect::addEffect(Effect *effect)
{
    effects.push_back(effect);
}

bool CompoundEffect::Init(AttrMap attrmap)
{
     return true;
}



EffectSequence::EffectSequence()
    : CompoundEffect("EffectSequence")
{

}

void EffectSequence::Render(SDL_Surface *screen)
{
    (*current)->Render(screen);
}

void EffectSequence::prepare()
{
    current = effects.begin();
    (*current)->prepare();
}

void EffectSequence::newTick(Uint32 ticks)
{
    (*current)->newTick(ticks);

    if ((*current)->isDone(current_ticks)) {
	++current;
	if (current != effects.end())
	    (*current)->prepare();
	current_ticks = 0;
    }
    current_ticks++;
}

bool EffectSequence::isDone(Uint32 ticks)
{
    return current == effects.end();
}

ParallelEffect::ParallelEffect()
    : CompoundEffect("ParallelEffect")
{

}

void ParallelEffect::Render(SDL_Surface *screen)
{
    for (EffectList::iterator i = effects.begin(); i != effects.end(); ++i)
	(*i)->Render(screen);
}

void ParallelEffect::prepare()
{
    for (EffectList::iterator i = effects.begin(); i != effects.end(); ++i)
	(*i)->prepare();
}    

void ParallelEffect::newTick(Uint32 ticks)
{
    for (EffectList::iterator i = effects.begin(); i != effects.end(); ++i)
	(*i)->newTick(ticks);
}

}
