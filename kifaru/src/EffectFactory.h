// -*- C++

#include <map>

namespace ephidrena
{

class Effect;

class EffectFactory
{
private:
    static EffectFactory *m_instance;

    typedef std::map<std::string, Effect *> EffectMap;
    EffectMap effects;

    EffectFactory();

public:
    Effect *createEffect(const char *name);
    void registerEffect(const char *name, Effect *effect);

    static EffectFactory *instance() {
	if (!m_instance)
	    m_instance = new EffectFactory;
	return m_instance;
    }
};

template<class C>
class EffectRegistrator
{
public:
    EffectRegistrator(const char *name) {
	C *effect = new C;
	EffectFactory::instance()->registerEffect(name, effect);
    }
};

#define REGISTER_EFFECT(className) static EffectRegistrator<className> Internal_EffectRegistrator_##className (""#className)

}
