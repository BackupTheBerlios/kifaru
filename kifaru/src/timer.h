#include <SDL/SDL.h>

namespace ephidrena{

class Timer
{
private:
    SDL_TimerID timer_id;
 
public:
    Timer();
    ~Timer();
    void Install();
    Uint32 Benchmark();
    static Uint32 PushSequencerEvent(Uint32 interval, void* param);     /*Static pga callback */

};

};
