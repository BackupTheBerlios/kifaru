#include "EngineTest.h"

namespace ephidrena
{

TestTD::TestTD()
	: Effect ("TestTD")
{

}

TestTD::~TestTD()
{
	
}

bool TestTD::Init(AttrMap attrmap)
{
	boxVerts = Vector3D(10,10,10);

	
	return true;
}

void TestTD::Render(SDL_Surface* screen)
{
	
}

}
