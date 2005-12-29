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

#ifdef __APPLE__
#include <CFBundle.h>
#endif

namespace ephidrena
{

class Kifaru
{
public:
	std::string locateDataFile(const std::string &name);
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
