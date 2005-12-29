// -*- C++ -*-

#include <tinyxml.h>
#include <tinystr.h>
#include <stack>

namespace ephidrena
{

class Scheduler;
class CompoundEffect;

class ScriptParser
{
	std::stack<CompoundEffect *> effect_stack;
	Scheduler *m_scheduler;
	bool parse_success;

public:
	ScriptParser();

	bool parse(const std::string &filename, Scheduler *sched);
	bool parseElement(TiXmlNode *elements, CompoundEffect *ce);
};

}
