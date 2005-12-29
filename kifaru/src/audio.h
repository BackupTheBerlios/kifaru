#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

namespace ephidrena {

class Audio
{
 private:

	int Rate,Channels,Buffers;
	Uint16 Format; 
	Mix_Music *musikk;
  
 public:
	Audio();
	~Audio();
	void InitOgg(const std::string &filename);
	void PlayOgg();
	Uint32 OggPosition();
};

};
