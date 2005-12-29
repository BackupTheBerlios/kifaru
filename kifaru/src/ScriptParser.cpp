#include "ScriptParser.h"
#include "CompoundEffect.h"
#include "EffectFactory.h"
#include "scheduler.h"
#include "tools.h"
#include <string>
#include <iostream>

using namespace std;

namespace ephidrena
{

enum Tags 
{
	t_Empty,
	t_Sequence,
	t_Parallel,
	t_Effect,
	t_Exit
};

static std::map<std::string, Tags> s_mapTags;

void InitEnum()
{
	s_mapTags["empty"]    = t_Empty;
	s_mapTags["sequence"] = t_Sequence;
	s_mapTags["parallel"] = t_Parallel;
	s_mapTags["effect"]   = t_Effect;
	s_mapTags["exit"]     = t_Exit;
}


ScriptParser::ScriptParser()
{
	InitEnum();
}

bool ScriptParser::parse(const char *filename, Scheduler *sched)
{
	m_scheduler = sched;
	TiXmlDocument *script = new TiXmlDocument(filename);
	CompoundEffect *ce = NULL; 
	Effect *effect;
    	TiXmlElement *demo = NULL;
    	TiXmlNode *sequence = NULL;
	TiXmlNode *elements = NULL;
    	int elemCount = 0;
    
    	if(!script->LoadFile())
	{
		cerr << "Script failed to load!" << endl; 
		delete script;
		return false;
	}

	demo = script->FirstChildElement("demo");
	if(!demo)
		goto parseError;
	
	sequence = demo->FirstChild("sequence");
	elements = 0;
	if(!parseElement(sequence,ce))
		goto parseError;

	while(elements = sequence->IterateChildren(elements))
	{
		if(!parseElement(elements,ce))
			goto parseError;
 	}
	effect_stack.pop();
	
	return true;

parseError:
	script->Clear();
	delete script;
	return false;
}

bool ScriptParser::parseElement(TiXmlNode *elements, CompoundEffect *ce)
{

	Effect *effect;

	s_mapTags["empty"]    = t_Empty;
	s_mapTags["sequence"] = t_Sequence;
	s_mapTags["parallel"] = t_Parallel;
	s_mapTags["effect"]   = t_Effect;
	s_mapTags["exit"]     = t_Exit;

	switch(s_mapTags[elements->Value()])
	{
	case t_Exit :
        	std::cerr << "Found exit!" << std::endl;
        	break;

    	case t_Sequence :
        	std::cerr << "Found sequence" << std::endl;
        	ce = new EffectSequence;
        	effect = ce;
        	break;

	case t_Parallel :
		std::cerr << "Found parallel" << std::endl;
		ce = new ParallelEffect;
		effect = ce;
		break;

	case t_Effect :
		std::cerr << "Found effect" << std::endl;

		if (effect_stack.empty()) 
		{
			std::cerr << "<effect> can only be used inside <parallel> or <sequence>"
				<< std::endl;
			return false;
		}
		
		Effect::AttrMap attrmap;
		TiXmlAttribute* attr;
		attr = elements->ToElement()->FirstAttribute();
		
		while(attr)    
		{
			cout << attr->Name() << "=" << attr->Value() << endl;
			attrmap.insert(
			Effect::AttrMap::value_type(
				attr->Name(), attr->Value() ) );
			attr = attr->Next();
		}
	
        	Effect::AttrMap::const_iterator it = attrmap.find("class");
		
		if (it == attrmap.end()) 
		{
            		std::cerr << "<effect> with no name" << std::endl;
            		return false;
		}

		std::cerr << "Mekker effekt av typen " << it->second;

		effect = EffectFactory::instance()->createEffect(it->second.c_str());

		it = attrmap.find("ticks");
		if (it != attrmap.end())
			effect->Ticks = str2int((char*)it->second.c_str());
		else
			effect-> Ticks = 65535;

		std::cout << " som varer i " << effect->Ticks << " ticks" << std::endl;

		effect->Init(attrmap);
		effect_stack.top()->addEffect(effect);
		break;
	}
			
	if (ce)
	{
		if (effect_stack.empty())
			m_scheduler->setRoot(ce);
		std::cerr << "Pusher effektgjeng" << std::endl;
		effect_stack.push(ce);
	}
	return true;
}

}
