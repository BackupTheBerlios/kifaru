#include "tools.h"
#include "effect.h"

namespace ephidrena {

	
int str2int(char* digit) {
   int result = 0;

   //--- Convert each digit char and add into result.
   while (*digit >= '0' && *digit <='9') {
      result = (result * 10) + (*digit - '0');
      digit++;
   }

   //--- Check that there were no non-digits at end.
   if (*digit != 0) {
      return false;
   }

   return result;
}

};
