// -*- C++ -*-

#include <list>

namespace ephidrena
{

class Effect;

class Scheduler
{
private:
    typedef std::list<Effect *> EffectList;
    EffectList effects;
    unsigned int frame_period;

public:    
    Scheduler();
    ~Scheduler();

    void EventHandler();

    void AddEffect(Effect *effect) {
	    effects.push_back(effect);
    }
};

};


