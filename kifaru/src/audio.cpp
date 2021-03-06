/* Ephidrena OggVorbis avspiller dings */
/* Ok andre fors�k bruker SDL_mixer og libvorbis */
/* burde v�re kompatibelt i b�tter og spann. */

#include <iostream>
#include <stdlib.h>
#include <memory>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "config.h"
#include "audio.h"

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

using namespace std;

namespace ephidrena
{

#ifdef __amigaos__
//vi m� gj�re lurt noe her!
#endif

#ifdef __MORPHOS__
//og sannsynligvis noe helt annet her!
#endif


Audio::Audio()
{
    
}

Audio::~Audio()
{
	Mix_FreeMusic(musikk);
}     
              

void Audio::InitOgg(const std::string &filename)
{
	Rate = 22050;
	Format = AUDIO_S16;
	Channels = 2;
	Buffers = 4096;
    
	if ( Mix_OpenAudio (Rate, Format, Channels, Buffers)) 
		cerr << "Unable to open audio device!" << endl;

#ifdef debug
	cerr << Mix_QuerySpec(&Rate, &Format, &Channels);
#endif

	musikk = Mix_LoadMUS(filename.c_str());
	//Mix_HookMusicFinished(musikkferdig);
	Mix_Volume(-1,MIX_MAX_VOLUME-(MIX_MAX_VOLUME/10));
}

void Audio::PlayOgg()
{
	cout << "skal starte musikken" << endl;
	Mix_PlayMusic(musikk,0);
	cout << "har starta musikken" << endl;
}


Uint32 Audio::OggPosition()
{

}


};
