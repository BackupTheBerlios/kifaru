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
    
	if (!parser.parse("effects.xml", &scheduler))
	{
		cerr << "Failed to parse script" << endl;
		return 1;
	}
	else
        	cerr << "Script parsed OK." << endl;
        
	timer.Install();
	audio.InitOgg("data/svart.ogg");
	audio.PlayOgg();
	scheduler.EventHandler();
    
	return 0;
}



