#include <iostream>
#include <stdlib.h>
#include "config.h"
#include "inits.h"
#include "audio.h"
#include "timer.h"
#include "scheduler.h"
#include "ScriptParser.h"

using namespace std;
using namespace ephidrena;

int main(int argc, char *argv[])
{
    Init init;
    Audio audio;
    Timer timer;
    Scheduler scheduler;
    ScriptParser parser;
   
    init.SDL();
    timer.Install();
    //audio.InitOgg("/home/zixaq/musikk/disparagement_disorder.ogg");
    //audio.InitOgg("msx/wireframes.ogg");
    audio.InitOgg("msx/Sursum_Corda.ogg");
    
    if (!parser.parse("effects.xml", &scheduler)) {
	cerr << "Failed to parse script" << endl;
	return 1;
    }
    
    audio.PlayOgg();
    scheduler.EventHandler();
    return 0;
}


