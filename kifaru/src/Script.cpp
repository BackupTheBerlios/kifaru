#include "Script.h"
#include "scheduler.h"
#include "EffectFactory.h"

#include <iostream>
#include <cerrno>

namespace ephidrena
{

Script::Script(const char *filename)
    : m_filename(filename)
{
    
}

bool Script::parse(Scheduler *sched)
{
    FILE *f;
    char *line = NULL;
    size_t buflen = 0;
    ssize_t len;
    bool retval = true;

    f = fopen(m_filename.c_str(), "r");
    if (!f) {
	std::cerr << "Could not open script " << m_filename
		  << ": " << strerror(errno) << std::endl;
	return false;
    }

    while ((len = getline(&line, &buflen, f)) != -1) {
	char *begin, *end;
	Effect *effect;

	if (line[0] == '#')
	    continue;

	// Ignore leading whitespace
	begin = line;
	while (len && isspace(begin[0]))
	    len--, begin++;
	if (!len)
	    continue;

	// Now, we should be able to find the name of an effect
	end = begin + 1;
	while (end < (begin + len) && !isspace(end[0]))
	    end++;

	end[0] = '\0';
	effect = EffectFactory::instance()->createEffect(begin);
	if (!effect) {
	    retval = false;
	    break;
	}

	sched->AddEffect(effect);
    }

    if (line)
	free(line);

    return retval;
}

}
