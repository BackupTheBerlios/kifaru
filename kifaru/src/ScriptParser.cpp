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

using xmlpp::SaxParser;

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
    parse_success = true;
    m_scheduler = sched;
    parse_file(filename);
    return parse_success;
}

void ScriptParser::on_error(const std::string &text)  	
{
    std::cerr << "Parse error: " << text;
    parse_success = false;
}

void ScriptParser::on_fatal_error(const std::string &text)  	
{
    std::cerr << "Fatal parse error: " << text << std::endl;
    parse_success = false;
}


void ScriptParser::on_warning(const std::string &text)
{
    std::cerr << "Warning " << text << std::endl;

}


void ScriptParser::on_start_element(const Glib::ustring &name,
				    const SaxParser::AttributeList &attributes)
{
    CompoundEffect *ce = NULL;
    Effect *effect;

    switch(s_mapTags[name])
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
	if (effect_stack.empty()) {
	    std::cerr << "<effect> can only be used inside <parallel> or <sequence>"
		      << std::endl;
	    return;
	}
	
	Effect::AttrMap attrmap;
	for (SaxParser::AttributeList::const_iterator i = attributes.begin();
	     i != attributes.end(); ++i) {
	    
	    attrmap.insert(Effect::AttrMap::value_type(i->name, i->value));
	}
	
	Effect::AttrMap::const_iterator it;
	
	it = attrmap.find("class");
	if (it == attrmap.end()) {
	    std::cerr << "<effect> with no name" << std::endl;
	    return;
	}
	
	std::cerr << "Mekker effekt av typen " << it->second;
	
	effect = EffectFactory::instance()->createEffect(it->second.c_str());
	
	it = attrmap.find("ticks");
	if (it != attrmap.end()) 
		effect->Ticks = str2int((char*)it->second.c_str());
	else
		effect-> Ticks = -1;

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
}

void ScriptParser::on_end_element(const Glib::ustring &name)
{
    if (name == "sequence" || name == "parallel") 
    {
	std::cerr << "Popper effektgjeng" << std::endl;
	effect_stack.pop();
    }
}


}
