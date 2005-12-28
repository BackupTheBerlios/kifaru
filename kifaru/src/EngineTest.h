#include "effect.h"
#include "Engine.h"
#include <SDL/sge.h>
#include <map>

namespace ephidrena
{

class TestTD : public Effect
{
 private:	
	 Vector3D boxVerts;
	 Uint32 boxEdge[12];
	 
 public:
	 TestTD();
	 ~TestTD();
	bool Init(AttrMap);
	void Render(SDL_Surface*);
};

}
