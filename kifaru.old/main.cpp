#include <iostream>
#include <stdlib.h>

#include "inits.h"
#include "audio.h"
#include "timer.h"
#include "scheduler.h"
#include "effect.h"

using namespace std;
using namespace ephidrena;

int main(int argc, char *argv[])
{
    Init init;
    Audio audio;
    Timer timer;
    Scheduler scheduler;
   
    init.SDL();
    timer.Install();
    audio.InitOgg("msx/wireframes.ogg");
    audio.PlayOgg();
    scheduler.EventHandler();
    return 0;
}
