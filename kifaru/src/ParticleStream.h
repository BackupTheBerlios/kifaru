#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/sge.h>
#include "config.h"
#include "primitives.h"
#include "tools.h"

namespace ephidrena{

class Particle 
{
private:
	void		iteratePos();
	void		stepTrajectory();
	void		setTrajectory();
	Uint32*		trajectory;	
public:
	Particle();
	~Particle();
	void 		Init();
	SDL_Surface*	getParticle();
	
	Uint32		alpha;
	Uint32		gamma;
	Uint32		colorkey;
	Uint32		speed;
	Uint32		weight;
	Sint32		magnetism;
	Uint32		xPos, yPos, zPos;
	Uint32		age;
	Uint32*		trajectoryPos;
};

class Stream : public Effect
{
    	const char *    m_name;
private:
	void		iterateParticles();
	void		drawParticles();
	void		preScaleParticle(SDL_Surface*);
	Uint32*		currentParticle;	
	SDL_Surface	workScreen();
public:
	Stream();
	~Stream();
	void		Render(SDL_Surface*);
	void		Init(AttrMap);
	SDL_Surface*	scaledParticles[256];
	Particle*	particles;
	Uint32		particleCount;
	Uint32		fieldOfView;
	Uint32		distance;
	Uint32		speed;
	Uint32		colorKey;
	Uint8		alpha;
	Uint8		alpha_max;
	Uint8		alpha_min;
	Uint8		gamma;
};

};
