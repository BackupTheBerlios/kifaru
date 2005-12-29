#include <iostream>
#include <stdlib.h>
#include "config.h"
#include "inits.h"
#include "audio.h"
#include "timer.h"
#include "scheduler.h"
#include "ScriptParser.h"
#include "Kifaru.h"

using namespace std;
using namespace ephidrena;

int main(int argc, char *argv[])
{
	Init init;
	Audio audio;
	Timer timer;
	Scheduler scheduler;
	ScriptParser parser;
	std::string script_path;
	std::string music_path;
	Kifaru *k = Kifaru::instance();

	init.SDL();
    
	if (!k->locateDataFile("effects.xml", script_path)) {
		k->error() << "Unable to locate effects.xml" << std::endl;
		return 1;
	}
	
	if (!parser.parse(script_path, &scheduler))
	{
		cerr << "Failed to parse script" << endl;
		return 1;
	}
	else
		cerr << "Script parsed OK." << endl;
        
	timer.Install();
	if (!k->locateDataFile("wireframes.ogg", music_path)) {
		k->error() << "Unable to locate wireframes.ogg" << std::endl;
		return 1;
	}
	audio.InitOgg(music_path);
	audio.PlayOgg();
	scheduler.EventHandler();
    
	return 0;
}
