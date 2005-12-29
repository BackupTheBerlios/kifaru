/*
 *  Kifaru.cpp
 *  kifaru
 *
 *  Created by HŒvard Skinnemoen on 12/28/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "Kifaru.h"

#include <iostream>
#include <SDL/SDL_image.h>

namespace ephidrena
{

Kifaru *Kifaru::m_instance;

Kifaru::Kifaru()
	: error_stream(&std::cerr)
{
#ifdef __APPLE__
	main_bundle = CFBundleGetMainBundle();
#else
	// TODO: Figure out a prefix that makes sense
	prefix = "/Users/hskinnemoen/src/kifaru";
#endif
}

bool Kifaru::locateDataFile(const std::string &name, std::string &path)
{
#ifdef __APPLE__
	CFStringRef name_ref, path_ref;
	CFURLRef url;
	
	std::cerr << "Hvor er '" << name << "' hen?" << std::endl;
	
	name_ref = CFStringCreateWithCStringNoCopy(NULL, name.c_str(), kCFStringEncodingUTF8, NULL);
	url = CFBundleCopyResourceURL(main_bundle, name_ref, NULL, NULL);
	if (!url)
		return false;
	path_ref = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
	CFRelease(url);
	
	// CFStringGetCStringPtr() is useless, so we have to do it the hard way.
	int buffer_length = CFStringGetLength(path_ref) + 1;
	char c_path[buffer_length];
	CFStringGetCString(path_ref, c_path, buffer_length, kCFStringEncodingUTF8);
	CFRelease(path_ref);
	
	std::cerr << "Den er her: " << c_path << std::endl;
	
	path = std::string(c_path);
	return true;
#else
	path = prefix;
	
	path.append("/data/");
	path.append(name);
	
	if (access(path.c_str(), R_OK))
		return false;
	
	return true;
#endif
}

SDL_Surface *Kifaru::loadTexture(const std::string &name)
{
	std::string path;
	SDL_RWops *rwop;
	
	if (!locateDataFile(name, path))
		return NULL;
	
	rwop = SDL_RWFromFile(path.c_str(), "rb");
	if (!rwop)
		return NULL;
	
	return IMG_Load_RW(rwop, true);
}

std::ostream &Kifaru::error()
{
	return *error_stream;
}

}