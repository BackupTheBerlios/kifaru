// -*- C++ -*-

#include "effect.h"

#include <vector>

struct SDL_Surface;

namespace ephidrena
{

class CompoundEffect : public Effect
{
protected:
    typedef std::vector<Effect *> EffectList;
    EffectList effects;

public:
    void addEffect(Effect *effect);

protected:
    CompoundEffect(const char *name)
	: Effect(name) { }
};

class EffectSequence : public CompoundEffect
{
    EffectList::iterator current;
    Uint32 current_ticks;

public:
    EffectSequence();
    
    virtual void Render(SDL_Surface *);
    virtual void prepare();
    virtual void newTick(Uint32 ticks);
    virtual bool isDone(Uint32 ticks);
};

class ParallelEffect : public CompoundEffect
{
public:
    ParallelEffect();

    virtual void Render(SDL_Surface *);
    virtual void prepare();
    virtual void newTick(Uint32 ticks);
};

}
