#include "tools.h"
#include "effect.h"

namespace ephidrena {

	

int str2int(const char* digit) {
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
float str2float(const char* digit) {
   float result = 0;
   float divider = 1;

   //--- Convert each digit char and add into result.
   while (*digit >= '0' && *digit <= '9')
   {
      result = (result * 10) + (*digit - '0');
      digit++;
   }
   
   if (*digit == '.') 
   {
	digit++;
   	while (*digit >= '0' && *digit <= '9')
	{
      		result = (result * 10) + (*digit - '0');
		divider *=10 ;
      		digit++;
	}	   
	result /= divider;
   }   

   //--- Check that there were no non-digits at end.
   if (*digit != 0) {
      return false;
   }

   return result;
}
};
