#include <SDL/SDL.h>

namespace ephidrena
{

extern SDL_Surface *screen;
extern SDL_Surface *pic1;
extern SDL_Surface *pic2;


class Init
{
 private:
 
 public:
      Init();
      ~Init();
      void SDL();
      void Images();
      
};

};
