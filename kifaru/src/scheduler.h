// -*- C++ -*-

namespace ephidrena
{

class Effect;

class Scheduler
{
private:
    Effect *root_effect;

public:    
    Scheduler();
    ~Scheduler();

    void EventHandler();

    void setRoot(Effect *effect) {
	root_effect = effect;
    }
};

};


