#include "ScriptParser.h"
#include "CompoundEffect.h"
#include "EffectFactory.h"
#include "scheduler.h"

#include <iostream>

namespace ephidrena
{

using xmlpp::SaxParser;

ScriptParser::ScriptParser()
{

}

bool ScriptParser::parse(const char *filename, Scheduler *sched)
{
    m_scheduler = sched;
    parse_file(filename);
}

void ScriptParser::on_start_element(const Glib::ustring &name,
				    const SaxParser::AttributeList &attributes)
{
    CompoundEffect *ce = NULL;
    Effect *effect;

    if (name == "sequence") {
	std::cerr << "Mekker sekkvens" << std::endl;
	ce = new EffectSequence;
	effect = ce;
    } else if (name == "parallel") {
	std::cerr << "Fy søren! Flere effekter på en gang!" << std::endl;
	ce = new ParallelEffect;
	effect = ce;
    } else if (name == "effect") {
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
	// TODO: Call Init()
	effect_stack.top()->addEffect(effect);
    }

    if (ce) {
	if (effect_stack.empty())
	    m_scheduler->setRoot(ce);
	std::cerr << "Pusher effektgjeng" << std::endl;
	effect_stack.push(ce);
    }
}

void ScriptParser::on_end_element(const Glib::ustring &name)
{
    if (name == "sequence" || name == "parallel") {
	std::cerr << "Popper effektgjeng" << std::endl;
	effect_stack.pop();
    }
}

}
