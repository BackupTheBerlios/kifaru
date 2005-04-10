#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/sge.h>
#include "config.h"
#include "primitives.h"
#include "tools.h"

#define ZMAX 1024
#define ZSCALES 64
#define PARTICLES 700

namespace ephidrena{

class Particle 
{
private:
	void		iteratePos();
	void		stepTrajectory();
	void		setTrajectory();
	void		Move(bool*, signed int*, int, int, int);
	void		ZField(int*, int, int);
	void		GravityPull(bool*, int*, int);
	Uint32*		trajectory;	
public:
	Particle();
	~Particle();
	void 		Init(SDL_Surface**);
	void		Run();
	void		Resurrect();
	
	Uint32		alpha;
	Uint32		gamma;
	Uint32		colorkey;
	Sint32		xspeed,yspeed,zspeed;
	bool		xdir, ydir, zdir;
	Uint32		weight;
	Sint32		magnetism;
	Sint32		xPos, yPos, zPos;
	Uint32		age;
	Uint32		lifeSpan;
	Uint32*		trajectoryPos;

};

class Stream : public Effect
{
    	const char *    m_name;
private:
	void		iterateParticles();
	void		drawParticles();
	void		preScaleParticle(SDL_Surface*);
	void		blurSurface(SDL_Surface*, int);
	void		shadeSurface(SDL_Surface*, int);
	Uint32*		currentParticle;	
	SDL_Surface	workScreen();
	Uint32		distance;
	Uint32		k;
public:
	Stream();
	~Stream();
	void		Render(SDL_Surface*);
	void		Init(AttrMap);

	Uint32		fieldOfView;
	Uint32		speed;
	Uint32		colorKey;
	Uint32		preScaleCount;
	Uint32		particleCount;
	Uint8		alpha;
	Uint8		alpha_max;
	Uint8		alpha_min;
	Uint8		gamma;
	
	SDL_Surface*	backdrop;
	SDL_Surface*	scaledParticles[ZSCALES];
	Uint32		scaledSize[ZSCALES];
	Particle*	particles[PARTICLES];
};

};
