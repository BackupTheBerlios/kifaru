// -*- C++ -*-

#include <SDL/SDL.h>
#include <map>


namespace ephidrena
{

class Effect
{
	const char* m_name;

 public:
    
	typedef std::map<std::string, std::string> AttrMap;
	int Ticks;

	virtual int ticks();
	Effect(const char *name);

	virtual ~Effect();
	void SLock(SDL_Surface *screen);
	void SULock(SDL_Surface *screen);
	void ClearScreen(SDL_Surface *screen);

	/* Abstract method (must be implemented by all subclasses) */
	virtual void Render(SDL_Surface*) = 0;

	virtual void prepare();
	virtual void newTick(Uint32 ticks);
	virtual bool isDone(Uint32 ticks);

	virtual bool Init(AttrMap) = 0;

	virtual void LoadBMP();
	virtual void LoadPNG();
    
	SDL_Surface *workscreen;
	Uint32 StartTime;
	Uint32 StopTime;  
	bool WaitRetrace;
	Uint32 MaxFramerate;
	Uint8 Brightness;
	Uint8 PostProcessAlpha;

	char* fileName;
	Uint32 xofs,yofs;

	const char* name() const 
	{
		return m_name;
    	}
};

class Jall : public Effect
{
 private:
    
 public:
	Jall();
	~Jall();
	bool Init(AttrMap);
	void Render (SDL_Surface*);
};

class Jull : public Effect
{
 private:

 public:
	Jull();
	~Jull();
	bool Init(AttrMap);
	void Render (SDL_Surface*);
};

class TD : public Effect
{
    
 private:

 public:
	TD();
	~TD();
	bool Init(AttrMap);
	void Render (SDL_Surface*, SDL_Surface*, Uint32, Uint32);

};

}
