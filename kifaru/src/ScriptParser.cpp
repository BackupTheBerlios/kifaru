#include "ScriptParser.h"
#include "CompoundEffect.h"
#include "EffectFactory.h"
#include "scheduler.h"

#include <string>
#include <iostream>

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
//    s_mapTags["Effect"]   = _Effect;
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
    std::cerr << text;
    parse_success = false;
}

void ScriptParser::on_fatal_error(const std::string &text)  	
{
    std::cerr << text;
    parse_success = false;
}


void ScriptParser::on_warning(const std::string &text)
{
    std::cerr << text;

}


void ScriptParser::on_start_element(const Glib::ustring &name,
				    const SaxParser::AttributeList &attributes)
{
    CompoundEffect *ce = NULL;
    Effect *effect;

    switch(s_mapTags[name])
    {
    case t_Sequence :

	std::cerr << "Mekker sekkvens" << std::endl;
	ce = new EffectSequence;
	effect = ce;
	break;
	
	
    case t_Parallel :
	
	std::cerr << "Fy søren! Flere effekter på en gang!" << std::endl;
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
	
	std::cerr << "Mekker effekt som heter " << it->second << std::endl;
	
	effect = EffectFactory::instance()->createEffect(it->second.c_str());
	
	it = attrmap.find("ticks");

	effect->Ticks = string2int((char*)it->second.c_str());
	std::cout << "Den varer i " << effect->Ticks << " ticks" << std::endl;

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


int ScriptParser::string2int(char* digit) {
   int result = 0;

   //--- Convert each digit char and add into result.
   while (*digit >= '0' && *digit <='9') {
      result = (result * 10) + (*digit - '0');
      digit++;
   }

   //--- Check that there were no non-digits at end.
   if (*digit != 0) {
      return false;
   }

   return result;
}




}
