#include <iostream>
#include <stdlib.h>
#include "config.h"
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
    Effect *effect;
   
    init.SDL();
    timer.Install();
    audio.InitOgg("msx/wireframes.ogg");
    audio.PlayOgg();
    
    effect = new Image;
    effect->fileName = "gfx/alphapartikkel1.png";
    effect->LoadPNG();
    effect->xofs = 0;
    effect->yofs = 24;
    scheduler.AddEffect(effect);
    scheduler.AddEffect(new Jall);

    scheduler.EventHandler();
    return 0;
}