/*
 *  Kifaru.h
 *  kifaru
 *
 *  Created by HŒvard Skinnemoen on 12/28/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include <string>
#include <ostream>
#include <SDL/SDL.h>

#ifdef __APPLE__
#include <CFBundle.h>
#endif

namespace ephidrena
{

class Kifaru
{
public:
	/**
	 * Locate a data file bundled with the demo.
	 * @arg name The name of the resource
	 * @arg path Where to store the full path of the specified resource
	 * @return true on success, false on error
	 */
	bool locateDataFile(const std::string &name, std::string &path);
	SDL_Surface *loadTexture(const std::string &name);
	std::ostream &error();
	
	static Kifaru *instance() {
		if (!m_instance)
			m_instance = new Kifaru;
		return m_instance;
	}

protected:
	Kifaru();

private:
	static Kifaru *m_instance;
	
	std::ostream *error_stream;

#ifdef __APPLE__
	CFBundleRef main_bundle;
#else
	std::string prefix;
#endif
	
	Kifaru(const Kifaru &);
	Kifaru &operator=(const Kifaru &);
};

}
