namespace ephidrena
{

class Effect
{
 public:
                    Effect();
    virtual         ~Effect();
    void            SLock(SDL_Surface *screen);
    void            SULock(SDL_Surface *screen);
    virtual void    Render(SDL_Surface*);
    virtual void    LoadBMP();
    virtual void    LoadPNG();
    
    SDL_Surface     *workscreen;
    Uint32          StartTime;
    Uint32          StopTime;  
    bool            WaitRetrace;
    Uint32          MaxFramerate;
    Uint8           Brightness;
    Uint8           PostProcessAlpha;

    char            *fileName;
    Uint32          xofs,yofs;

};

class Jall : public Effect
{
 private:
    
 public:
    Jall();
    ~Jall();
    void Render (SDL_Surface*);
};

class TD : public Effect
{
    
 private:

 public:
    TD();
    ~TD();
    void Render (SDL_Surface*, SDL_Surface*, Uint32, Uint32);

};


class Image : public Effect
{
 private:
     SDL_Surface       *pic;   
 public:
     Image();
    ~Image();
    void Render(SDL_Surface*);
    Uint32            xofs,yofs;
    void    LoadBMP();
    void    LoadPNG();
  
 
};


};
