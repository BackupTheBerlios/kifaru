// -*- C++ -*-

#include <string>

namespace ephidrena
{

class Scheduler;

class Script
{
    const std::string m_filename;

public:
    Script(const char *filename);

    bool parse(Scheduler *sched);
};

}
