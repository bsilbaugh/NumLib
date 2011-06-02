/*! \file string_utils.h
 */

#include "string_utils.h"

namespace numlib{ namespace io{

void stripWhiteSpace(String & s, const char* whitespace)
{
	 Size len = s.length();

	 for(const char* w = whitespace; *w != '\0'; ++w)
	 {
		  Size pos = 0;
		  while(pos < len)
		  {
			   while(s[pos] == *w)
					s.erase(pos,1);
			   ++pos;
		  }
	 }
}

void stripComments(String & s, char cc)
{
	 Size pos;
	 pos = s.find(cc);
	 if(pos != String::npos)
		  s.erase(pos);
}

}//::numlib::io
