#include <iostream>
#include <stdlib.h>
#include "config.h"
#include "inits.h"
#include "audio.h"
#include "timer.h"
#include "scheduler.h"
#include "Script.h"

using namespace std;
using namespace ephidrena;

int main(int argc, char *argv[])
{
    Init init;
    Audio audio;
    Timer timer;
    Scheduler scheduler;
    Script script("effects.script");
   
    init.SDL();
    timer.Install();
    audio.InitOgg("msx/wireframes.ogg");
    audio.PlayOgg();
    
    if (!script.parse(&scheduler)) {
	cerr << "Failed to parse script" << endl;
	return 1;
    }
    
#if 0
    effect = factory->createEffect("Image");
    effect->fileName = "gfx/alphapartikkel1.png";
    effect->LoadPNG();
    effect->xofs = 0;
    effect->yofs = 24;
    scheduler.AddEffect(effect);
    scheduler.AddEffect(factory->createEffect("Jall"));
#endif

    scheduler.EventHandler();
    return 0;
}
