// -*- C++ -*-

#include <libxml++/libxml++.h>
#include <stack>

namespace ephidrena
{

class Scheduler;
class CompoundEffect;

class ScriptParser : public xmlpp::SaxParser
{
    std::stack<CompoundEffect *> effect_stack;
    Scheduler *m_scheduler;

public:
    ScriptParser();

    bool parse(const char *filename, Scheduler *sched);

protected:
    virtual void on_start_element(const Glib::ustring &name,
				  const xmlpp::SaxParser::AttributeList &attributes);
    virtual void on_end_element(const Glib::ustring &name);
};

}
