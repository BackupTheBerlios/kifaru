#include "EffectFactory.h"

#include <iostream>
#include <cstdlib>

namespace ephidrena
{

EffectFactory *EffectFactory::m_instance;

EffectFactory::EffectFactory()
{

}

Effect *EffectFactory::createEffect(const char *name)
{
    EffectMap::iterator it;

    it = effects.find(name);
    if (it == effects.end()) {
	std::cerr << "Warning: Could not find effect \"" << name << "\""
		  << std::endl;
	return NULL;
    }

    return it->second->createEffect();
}

void EffectFactory::registerEffect(const char *name, EffectCreator *effect)
{
    std::cout << "registerEffect: " << name << std::endl;

    effects.insert(EffectMap::value_type(name, effect));
}

EffectCreator::EffectCreator()
{

}

}
