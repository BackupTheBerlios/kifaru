
namespace ephidrena
{
class Scheduler
{
private:
    Uint32 CurrentFX,NextFX;

public:    
    static Uint32 Clock;
 
    Scheduler();
    ~Scheduler();     
    void EventHandler();
};

class FXList : public Scheduler
{

private:


public:
    FXList();
    ~FXList();
    Uint32 CheckTime();  
  
};


};


