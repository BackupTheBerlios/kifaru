#include <map>
#include <string>

namespace ephidrena{
    	typedef std::map<std::string, std::string> AttrMap;
	
	int str2int(char *str);
	int getAtValue(AttrMap, const char*);
	int getAtText (AttrMap , const char*);

}
