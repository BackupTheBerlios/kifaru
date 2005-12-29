// -*- C++ -*-

#include <map>

namespace ephidrena
{

class Effect;
class EffectCreator;

class EffectFactory
{
private:
	static EffectFactory *m_instance;

	typedef std::map<std::string, EffectCreator *> EffectMap;
	EffectMap effects;

	EffectFactory();

public:
	Effect *createEffect(const char *name);
	void registerEffect(const char *name, EffectCreator *effect);

	static EffectFactory *instance()
	{
		if (!m_instance)
			m_instance = new EffectFactory;
		return m_instance;
	}
};

class EffectCreator
{
public:
	virtual Effect *createEffect() = 0;

protected:
	EffectCreator();
};

template<class C>
class ConcreteEffectCreator : public EffectCreator
{
public:
	ConcreteEffectCreator(const char *name)
	{
		EffectFactory::instance()->registerEffect(name, this);
    	}

	virtual Effect *createEffect()
	{
		C *effect = new C;
		return effect;
	}
};

#define REGISTER_EFFECT(className) static ConcreteEffectCreator<className> Internal_EffectRegistrator_##className (""#className)

}
